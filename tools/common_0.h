struct Vector3 {
  float x;
  float y;
  float z;
};

inline void to_json(nlohmann::json &json, Vector3 const &in_value) {
  VRMC::WriteField("x", json, in_value.x, 0.f);
  VRMC::WriteField("y", json, in_value.y, 0.f);
  VRMC::WriteField("z", json, in_value.z, 0.f);
}

inline void from_json(nlohmann::json const &json, Vector3 &out_value) {
  VRMC::ReadRequiredField("x", json, out_value.x);
  VRMC::ReadRequiredField("y", json, out_value.y);
  VRMC::ReadRequiredField("z", json, out_value.z);
}
