struct Vector3 : fx::gltf::NeverEmpty {
  float x;
  float y;
  float z;
};

inline void to_json(nlohmann::json &json, Vector3 const &in_value) {
  fx::gltf::detail::WriteField("x", json, in_value.x, 0.f);
  fx::gltf::detail::WriteField("y", json, in_value.y, 0.f);
  fx::gltf::detail::WriteField("z", json, in_value.z, 0.f);
}

inline void from_json(nlohmann::json const &json, Vector3 &out_value) {
  fx::gltf::detail::ReadRequiredField("x", json, out_value.x);
  fx::gltf::detail::ReadRequiredField("y", json, out_value.y);
  fx::gltf::detail::ReadRequiredField("z", json, out_value.z);
}
