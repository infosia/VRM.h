/**
 *
 * Sync vrm-specification schema JSON
 *
 * Distributed under the MIT License
 *
 */
'use strict'

const fs = require('fs');
const path = require('path');
const basepath = path.join(__dirname, '..', 'schema');

const files = [
'02.mtoon.shadingShiftTexture.schema.json',
'02.VRMC_springBone.colliderGroup.schema.json',
'02.VRMC_springBone.joint.schema.json',
'02.VRMC_springBone.shape.schema.json',
'02.VRMC_vrm.expressions.expression.materialColorBind.schema.json',
'02.VRMC_vrm.expressions.expression.morphTargetBind.schema.json',
'02.VRMC_vrm.expressions.expression.textureTransformBind.schema.json',
'02.VRMC_vrm.firstPerson.meshAnnotation.schema.json',
'02.VRMC_vrm.humanoid.humanBones.humanBone.schema.json',
'02.VRMC_vrm.lookAt.rangeMap.schema.json',
'02.VRMC_vrm.meta.schema.json',
'03.VRMC_node_constraint.rotationConstraint.schema.json',
'03.VRMC_node_constraint.rollConstraint.schema.json',
'03.VRMC_node_constraint.aimConstraint.schema.json',
'03.VRMC_springBone.collider.schema.json',
'03.VRMC_springBone.spring.schema.json',
'03.VRMC_vrm.humanoid.humanBones.schema.json',
'04.VRMC_node_constraint.constraint.schema.json',
'05.VRMC_springBone.schema.json',
'05.VRMC_vrm.expressions.expression.schema.json',
'05.VRMC_vrm.expressions.schema.json',
'05.VRMC_vrm.firstPerson.schema.json',
'05.VRMC_vrm.humanoid.schema.json',
'05.VRMC_vrm.lookAt.schema.json',
'VRMC_materials_hdr_emissiveMultiplier.json',
'VRMC_materials_mtoon.schema.json',
'VRMC_node_constraint.schema.json',
'VRMC_vrm.schema.json',
];

files.forEach(dst => {
  let src = dst;
  if (/^\d+\./.test(dst)) {
    src = dst.substring(3);
  }
  let dir = 'VRMC_vrm-1.0-beta';
  if (/^VRMC_node_constraint/.test(src)) {
    dir = 'VRMC_node_constraint-1.0_beta';
  } else if (/^VRMC_springBone./.test(src)) {
    dir = 'VRMC_springBone-1.0-beta';
  } else if (/^mtoon/.test(src)) {
    dir = 'VRMC_materials_mtoon-1.0-beta';
  } else if (/^VRMC_materials_mtoon/.test(src)) {
    dir = 'VRMC_materials_mtoon-1.0-beta';
  } else if (/^VRMC_materials_hdr_/.test(src)) {
    dir = 'VRMC_materials_hdr_emissiveMultiplier-1.0';
  }

  let dstPath = path.join('..', 'schema', '1.0', dst);
  let srcPath = path.join('..', '..', 'vrm-specification', 'specification',  dir, 'schema', src);

  fs.copyFileSync(srcPath, dstPath);
});
