/**
 * vrm_type_generator - generate C++ structs and enums from VRM specification
 *
 * Distributed under the MIT License, see notice at the end of this file.
 *
 */
"use strict"

const supportedVersions = ['0.0' ,'1.0'];

const fs = require('fs');
const path = require('path');
const basepath = path.join(__dirname, '..', 'schema');
const indent   = '\t';
const indent2  = indent + indent;

let out_structs = {};
let global_references = {};
let global_enums = {};

supportedVersions.forEach(version => {
	out_structs[version] = [];
	global_references[version] = {};
})

function sanitize(str) {
	return str.replace(/^(vrm\.|VRMC_?|\d+\.)/, '').replace(/\./g, '_').replace(/\s/g, '').replace(/_schema_json$/, '');
}

function capitalize(str) {
	return str[0].toUpperCase() + str.slice(1);
}

function snake_case(str) {
	let chars = [];
	for (let i = 0; i < str.length; i++) {
		if (i == 0 || str[i - 1] == '_') {
			chars.push(str[i].toUpperCase());
		} else if (str[i] != '_') {
			chars.push(str[i]);
		}
	}
	return chars.join('');
}

function select_native_type(type) {
	if (type == 'string')  return 'std::string';
	if (type == 'integer') return 'uint32_t';
	if (type == 'number')  return 'float';
	if (type == 'boolean') return 'bool';
	if (type == 'textureProperties') return 'uint32_t';
	if (type == 'floatProperties') return 'float';
	if (type == 'keywordMap') return 'bool';
	if (type == 'vectorProperties') return 'float[4]';
	if (type == 'tagMap') return 'std::string';
	return undefined;
}

function is_vec3(items) {
	return (items.properties && items.properties.x && items.properties.y && items.properties.z
		&& items.properties.x.type == 'number' && items.properties.y.type == 'number' && items.properties.z.type == 'number');
}

function write_enum(json, version, title) {
	let classname = capitalize(sanitize(title));
	if (global_enums[classname]) {
		return;	
	}
	global_enums[classname] = true;

	out_structs[version].push(indent + 'enum class ' + classname + ' : uint8_t {');
	out_structs[version].push(json.enum.map(value => {
		return indent2 + capitalize(value);
	}).join(',\n'));
	out_structs[version].push(indent + '};');
}

function cache_ref(json, file, version) {
	const id = json['$id'];
	if (id) {
		global_references[version][id] = json;
	} else if (/^\d{2}.ref\./.test(file)) {
		global_references[version][file.substring(7)] = json;
	} else if (/^\d{2}\./.test(file)) {
		global_references[version][file.substring(3)] = json;
	}
}

function get_object_type(name, json, allOf, version) {
	if (json.type) {
		return json.type;
	}

	if (allOf) {
		for (let i = 0; i < allOf.length; i++) {
			const global_ref = global_references[version][allOf[i]['$ref']];
			if (global_ref && global_ref.properties[name]) {
				const properties = global_ref.properties[name];
				const type = properties.type;
				if (type) {
					return type;
				} else if (properties.allOf && properties.allOf[0] 
					&& properties.allOf[0]['$ref'] == 'glTFid.schema.json') {
					return 'integer';
				}
			}
		}
	}

	return undefined;
}

function set(properties, primitive) {
	let value = properties['default'];
	if (value) {
		if (primitive == 'float') {
			if (value.toString().indexOf('.') == -1)
				value += '.';
			value += 'f';
		}

		return ' = ' + value;
	}
	return '';
}

function parse(json, file, version, parent) {
	if (!parent) {
		cache_ref(json, file, version);
	}

	if (/^\d{2}.ref\./.test(file)) {
		return;
	}

	const has_parent_class = parent && parent.title ? true : false;

	if (json.type == 'string' && json['enum'] && !has_parent_class) {
		write_enum(json, version, json.title);
	} else if (json.type == 'object' && json.properties) {

		if (!has_parent_class) {
			const structname = snake_case(sanitize(json.title ? json.title : file));
			out_structs[version].push('struct ' + structname + ' { ');
		}

		Object.keys(json.properties).forEach(name => {
			if (name == 'extensions' || name == 'extras') {
				return;
			}
			const properties = json.properties[name];
			const type = get_object_type(name, properties, json.allOf, version);
			const ref  = properties['$ref'];
			const primitive = select_native_type(type);
			const allOf = properties.allOf;

			if (type == 'string') {
				if (properties.enum) {
					write_enum(properties, version, properties.title ? properties.title : name);
				} else {
					out_structs[version].push(indent + 'std::string ' + name + set(properties) + ';');
				}
			} else if (primitive) {
				out_structs[version].push(indent + primitive + ' ' + name + set(properties, primitive) + ';');
			} else if (!ref && type == 'object') {
				if (is_vec3(properties)) {
					out_structs[version].push(indent + 'float ' + name + '[3];');
				} else if (name == 'floatProperties' || name == 'textureProperties' || name == 'keywordMap' || name == 'vectorProperties' || name == 'tagMap') {
					const value_type = select_native_type(name);
					out_structs[version].push(indent + 'std::unordered_map<std::string, ' + value_type + '> ' + name + ';');
				} else if (properties) {
					properties.title = name;
					parse(properties, file, version, name)
					if (properties.additionalProperties) {
						// can be ignored
					} else {
						const structname = snake_case(sanitize(name));
						out_structs[version].push(indent + structname + ' ' + name + ';');
					}
				} else {
					throw new Error('Unknown type: ' + json.type + ' for ' + name + ' in ' + file);
				}
			} else if (type == 'array') {
				const items = properties.items;
				if (items) {
					const ref  = items['$ref'];
					const primitives = select_native_type(items.type);
					if (ref) {
						const global_ref = global_references[version][ref];
						if (ref == 'glTFid.schema.json') {
							out_structs[version].push(indent + 'std::vector<uint32_t> ' + name + ';');
						} else if (global_ref) {
							let classname = snake_case(sanitize(global_ref.title ? global_ref.title : ref));
							out_structs[version].push(indent + 'std::vector<' + classname + '> ' + name + ';');
						} else {
							throw new Error('Unknown reference: ' + ref + ' for ' + name + ' in ' + file);
						}
					} else if (primitives) {
						out_structs[version].push(indent + 'std::vector<' + primitives + '> ' + name + ';');
					} else if (items.type == 'object') {
						const structname = snake_case(sanitize(name)).slice(0, -1);
						items.title = structname;
						parse(items, file, version, name);
						out_structs[version].push(indent + 'std::vector<' + structname + '> ' + name + ';');
					} else if (items.type == 'string') {
						out_structs[version].push(indent + 'std::vector<std::string> ' + name + ';');
					} else {
						throw new Error('Unknown type: ' + items.type + ' for ' + name + '.items in ' + file);
					}
				}
			} else if (ref) {
				const global_ref = global_references[version][ref];
				if (global_ref) {
					let classname = snake_case(sanitize(global_ref.title ? global_ref.title : ref));
					out_structs[version].push(indent + classname + ' ' + name + ';');
				} else {
					throw new Error('Unknown reference: ' + ref + ' for ' + name + ' in ' + file);
				}
			} else if (allOf) {
				for (let i = 0; i < allOf.length; i++) {
					const ref = allOf[i]['$ref'];
					const global_ref = global_references[version][ref];
					if (global_ref) {
						if (global_ref['$id'] == 'glTFid.schema.json') {
							out_structs[version].push(indent + 'uint32_t ' + name + ';');
						} else if (global_ref['$id'] == 'glTFProperty.schema.json') {
							// can be ignored
						} else if (global_ref['enum']) {
							const enumname = capitalize(sanitize(global_ref.title));
							out_structs[version].push(indent + enumname + ' ' + name + ';');
						} else if (global_ref.properties) {
							const structname = snake_case(sanitize(global_ref.title));
							out_structs[version].push(indent + structname + ' ' + name + ';');
						} else {
							throw new Error('Unhandled allOf reference: ' + ref + ' in ' + file);
						}
					} else {
						throw new Error('Unknown allOf reference: ' + ref + ' in ' + file);
					}
				}
			} else {
				throw new Error('Unknown type: ' + type + ' for ' + name + ' in ' + file);
			}
		});

		if (!has_parent_class) {
			out_structs[version].push(indent + 'nlohmann::json extensionsAndExtras{};');
			out_structs[version].push('};\n');
		}
	} else if (json.type == 'object' && json.additionalProperties) {
		const ref = json.additionalProperties['$ref'];
		const global_ref = global_references[version][ref];
		if (global_ref && parent) {
			const structname = snake_case(sanitize(global_ref.title));
			out_structs[version].push(indent + structname + ' ' + parent + ';');
		} else {
			throw new Error('Unhandled additionalProperties: ' + ref + ' in ' + file);
		}
	} else {
		throw new Error('Unknown type: ' + json.type + ' in ' + file);
	}
}

const header = fs.readFileSync(path.join(__dirname, 'header.txt'), 'utf8').toString();
const footer = fs.readFileSync(path.join(__dirname, 'footer.txt'), 'utf8').toString();
const output_stream = fs.createWriteStream(path.join(__dirname, '..', 'include', 'VRM.h'), 'utf8');
output_stream.write(header, 'utf8');

supportedVersions.forEach(version => {

	const v = version.replace(/\./, '_')

	output_stream.write('#ifdef USE_VRM_' + v + '\n\n', 'utf8');
	output_stream.write('namespace VRM_' + v + ' {\n', 'utf8');

	const schema_dir = path.join(basepath, version);
	const files = fs.readdirSync(schema_dir);
	files.filter(file => /.*\.json$/.test(file)).forEach(file => {
		const json = JSON.parse(fs.readFileSync(path.join(schema_dir, file), 'utf8'));
		parse(json, file, version);
	});

	output_stream.write(out_structs[version].join('\n'), 'utf8');
	output_stream.write('}\n', 'utf8');
	output_stream.write('#endif\n\n', 'utf8');
});

output_stream.write(footer, 'utf8');
output_stream.end();

/* vrm_type_generator is distributed under MIT license:
 *
 * Copyright (c) 2021 Kota Iguchi

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
