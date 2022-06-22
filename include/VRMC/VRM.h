/**
 * VRM.h - C++ header-only library for simple serialization/deserialization of
 * VRM 0.x and 1.0
 *
 * Distributed under the MIT License, see notice at the end of this file.
 *
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace VRMC {
template <typename TKey, typename TTarget>
inline void ReadRequiredField(TKey &&key, nlohmann::json const &json,
                              TTarget &target) {
  const auto iter = json.find(key);
  if (iter == json.end()) {
    std::string msg = "Required field not found : " + std::string(key);
    throw std::runtime_error(msg);
  }

  target = iter->template get<TTarget>();
}

template <typename TKey, typename TTarget>
inline void ReadOptionalField(TKey &&key, nlohmann::json const &json,
                              TTarget &target) {
  const auto iter = json.find(key);
  if (iter != json.end()) {
    target = iter->template get<TTarget>();
  }
}

template <typename TValue>
inline void WriteField(std::string const &key, nlohmann::json &json,
                       TValue const &value) {
  json[key] = value;
}

template <typename TValue>
inline void WriteField(std::string const &key, nlohmann::json &json,
                       TValue const &value, TValue const &defaultValue) {
  if (value != defaultValue) {
    json[key] = value;
  }
}
} // namespace VRMC
#ifdef USE_VRMC_VRM_0_0

namespace VRMC_VRM_0_0 {
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
struct SecondaryanimationSpring {
  std::string comment;
  float stiffiness{};
  float gravityPower{};
  Vector3 gravityDir{};
  float dragForce{};
  uint32_t center{};
  float hitRadius{};
  std::vector<uint32_t> bones{};
  std::vector<uint32_t> colliderGroups{};
};

struct SecondaryanimationCollidergroup {
  uint32_t node{};
  struct Collider {
    Vector3 offset{};
    float radius{};
  };

  std::vector<Collider> colliders{};
};

struct Secondaryanimation {
  std::vector<SecondaryanimationSpring> boneGroups{};
  std::vector<SecondaryanimationCollidergroup> colliderGroups{};
};

struct BlendshapeBind {
  uint32_t mesh{};
  uint32_t index{};
  float weight{};
};

struct BlendshapeMaterialbind {
  std::string materialName;
  std::string propertyName;
  std::vector<float> targetValue{};
};

struct BlendshapeGroup {
  std::string name;
  enum class PresetName : uint8_t {
    Unknown,
    Neutral,
    A,
    I,
    U,
    E,
    O,
    Blink,
    Joy,
    Angry,
    Sorrow,
    Fun,
    Lookup,
    Lookdown,
    Lookleft,
    Lookright,
    Blink_l,
    Blink_r
  };
  PresetName presetName;
  std::vector<BlendshapeBind> binds{};
  std::vector<BlendshapeMaterialbind> materialValues{};
  bool isBinary{};
};

struct Blendshape {
  std::vector<BlendshapeGroup> blendShapeGroups{};
};

struct FirstpersonDegreemap {
  std::vector<float> curve{};
  float xRange{};
  float yRange{};
};

struct FirstpersonMeshannotation {
  uint32_t mesh{};
  std::string firstPersonFlag;
};

struct Firstperson {
  uint32_t firstPersonBone{};
  Vector3 firstPersonBoneOffset{};
  std::vector<FirstpersonMeshannotation> meshAnnotations{};
  enum class LookAtTypeName : uint8_t { Bone, BlendShape };
  LookAtTypeName lookAtTypeName;
  FirstpersonDegreemap lookAtHorizontalInner{};
  FirstpersonDegreemap lookAtHorizontalOuter{};
  FirstpersonDegreemap lookAtVerticalDown{};
  FirstpersonDegreemap lookAtVerticalUp{};
};

struct HumanoidBone {
  enum class Bone : uint8_t {
    Hips,
    LeftUpperLeg,
    RightUpperLeg,
    LeftLowerLeg,
    RightLowerLeg,
    LeftFoot,
    RightFoot,
    Spine,
    Chest,
    Neck,
    Head,
    LeftShoulder,
    RightShoulder,
    LeftUpperArm,
    RightUpperArm,
    LeftLowerArm,
    RightLowerArm,
    LeftHand,
    RightHand,
    LeftToes,
    RightToes,
    LeftEye,
    RightEye,
    Jaw,
    LeftThumbProximal,
    LeftThumbIntermediate,
    LeftThumbDistal,
    LeftIndexProximal,
    LeftIndexIntermediate,
    LeftIndexDistal,
    LeftMiddleProximal,
    LeftMiddleIntermediate,
    LeftMiddleDistal,
    LeftRingProximal,
    LeftRingIntermediate,
    LeftRingDistal,
    LeftLittleProximal,
    LeftLittleIntermediate,
    LeftLittleDistal,
    RightThumbProximal,
    RightThumbIntermediate,
    RightThumbDistal,
    RightIndexProximal,
    RightIndexIntermediate,
    RightIndexDistal,
    RightMiddleProximal,
    RightMiddleIntermediate,
    RightMiddleDistal,
    RightRingProximal,
    RightRingIntermediate,
    RightRingDistal,
    RightLittleProximal,
    RightLittleIntermediate,
    RightLittleDistal,
    UpperChest
  };
  Bone bone;
  uint32_t node{};
  bool useDefaultValues{};
  Vector3 min{};
  Vector3 max{};
  Vector3 center{};
  float axisLength{};
};

struct Humanoid {
  std::vector<HumanoidBone> humanBones{};
  float armStretch{};
  float legStretch{};
  float upperArmTwist{};
  float lowerArmTwist{};
  float upperLegTwist{};
  float lowerLegTwist{};
  float feetSpacing{};
  bool hasTranslationDoF{};
};

struct Material {
  std::string name;
  std::string shader;
  uint32_t renderQueue{};
  std::unordered_map<std::string, float> floatProperties{};
  std::unordered_map<std::string, std::vector<float>> vectorProperties{};
  std::unordered_map<std::string, uint32_t> textureProperties{};
  std::unordered_map<std::string, bool> keywordMap{};
  std::unordered_map<std::string, std::string> tagMap{};
};

struct Meta {
  std::string title;
  std::string version;
  std::string author;
  std::string contactInformation;
  std::string reference;
  uint32_t texture{};
  enum class AllowedUserName : uint8_t {
    OnlyAuthor,
    ExplicitlyLicensedPerson,
    Everyone
  };
  AllowedUserName allowedUserName;
  enum class ViolentUssageName : uint8_t { Disallow, Allow };
  ViolentUssageName violentUssageName;
  enum class SexualUssageName : uint8_t { Disallow, Allow };
  SexualUssageName sexualUssageName;
  enum class CommercialUssageName : uint8_t { Disallow, Allow };
  CommercialUssageName commercialUssageName;
  std::string otherPermissionUrl;
  enum class LicenseName : uint8_t {
    Redistribution_Prohibited,
    CC0,
    CC_BY,
    CC_BY_NC,
    CC_BY_SA,
    CC_BY_NC_SA,
    CC_BY_ND,
    CC_BY_NC_ND,
    Other
  };
  LicenseName licenseName;
  std::string otherLicenseUrl;
};

struct Vrm {
  std::string exporterVersion;
  std::string specVersion;
  Meta meta{};
  Humanoid humanoid{};
  Firstperson firstPerson{};
  Blendshape blendShapeMaster{};
  Secondaryanimation secondaryAnimation{};
  std::vector<Material> materialProperties{};
};
inline void from_json(nlohmann::json const &json,
                      BlendshapeGroup::PresetName &out_value) {
  std::string type = json.get<std::string>();
  if (type == "unknown") {
    out_value = BlendshapeGroup::PresetName::Unknown;
  } else if (type == "neutral") {
    out_value = BlendshapeGroup::PresetName::Neutral;
  } else if (type == "a") {
    out_value = BlendshapeGroup::PresetName::A;
  } else if (type == "i") {
    out_value = BlendshapeGroup::PresetName::I;
  } else if (type == "u") {
    out_value = BlendshapeGroup::PresetName::U;
  } else if (type == "e") {
    out_value = BlendshapeGroup::PresetName::E;
  } else if (type == "o") {
    out_value = BlendshapeGroup::PresetName::O;
  } else if (type == "blink") {
    out_value = BlendshapeGroup::PresetName::Blink;
  } else if (type == "joy") {
    out_value = BlendshapeGroup::PresetName::Joy;
  } else if (type == "angry") {
    out_value = BlendshapeGroup::PresetName::Angry;
  } else if (type == "sorrow") {
    out_value = BlendshapeGroup::PresetName::Sorrow;
  } else if (type == "fun") {
    out_value = BlendshapeGroup::PresetName::Fun;
  } else if (type == "lookup") {
    out_value = BlendshapeGroup::PresetName::Lookup;
  } else if (type == "lookdown") {
    out_value = BlendshapeGroup::PresetName::Lookdown;
  } else if (type == "lookleft") {
    out_value = BlendshapeGroup::PresetName::Lookleft;
  } else if (type == "lookright") {
    out_value = BlendshapeGroup::PresetName::Lookright;
  } else if (type == "blink_l") {
    out_value = BlendshapeGroup::PresetName::Blink_l;
  } else if (type == "blink_r") {
    out_value = BlendshapeGroup::PresetName::Blink_r;
  }
}

inline void from_json(nlohmann::json const &json,
                      Firstperson::LookAtTypeName &out_value) {
  std::string type = json.get<std::string>();
  if (type == "Bone") {
    out_value = Firstperson::LookAtTypeName::Bone;
  } else if (type == "BlendShape") {
    out_value = Firstperson::LookAtTypeName::BlendShape;
  }
}

inline void from_json(nlohmann::json const &json,
                      HumanoidBone::Bone &out_value) {
  std::string type = json.get<std::string>();
  if (type == "hips") {
    out_value = HumanoidBone::Bone::Hips;
  } else if (type == "leftUpperLeg") {
    out_value = HumanoidBone::Bone::LeftUpperLeg;
  } else if (type == "rightUpperLeg") {
    out_value = HumanoidBone::Bone::RightUpperLeg;
  } else if (type == "leftLowerLeg") {
    out_value = HumanoidBone::Bone::LeftLowerLeg;
  } else if (type == "rightLowerLeg") {
    out_value = HumanoidBone::Bone::RightLowerLeg;
  } else if (type == "leftFoot") {
    out_value = HumanoidBone::Bone::LeftFoot;
  } else if (type == "rightFoot") {
    out_value = HumanoidBone::Bone::RightFoot;
  } else if (type == "spine") {
    out_value = HumanoidBone::Bone::Spine;
  } else if (type == "chest") {
    out_value = HumanoidBone::Bone::Chest;
  } else if (type == "neck") {
    out_value = HumanoidBone::Bone::Neck;
  } else if (type == "head") {
    out_value = HumanoidBone::Bone::Head;
  } else if (type == "leftShoulder") {
    out_value = HumanoidBone::Bone::LeftShoulder;
  } else if (type == "rightShoulder") {
    out_value = HumanoidBone::Bone::RightShoulder;
  } else if (type == "leftUpperArm") {
    out_value = HumanoidBone::Bone::LeftUpperArm;
  } else if (type == "rightUpperArm") {
    out_value = HumanoidBone::Bone::RightUpperArm;
  } else if (type == "leftLowerArm") {
    out_value = HumanoidBone::Bone::LeftLowerArm;
  } else if (type == "rightLowerArm") {
    out_value = HumanoidBone::Bone::RightLowerArm;
  } else if (type == "leftHand") {
    out_value = HumanoidBone::Bone::LeftHand;
  } else if (type == "rightHand") {
    out_value = HumanoidBone::Bone::RightHand;
  } else if (type == "leftToes") {
    out_value = HumanoidBone::Bone::LeftToes;
  } else if (type == "rightToes") {
    out_value = HumanoidBone::Bone::RightToes;
  } else if (type == "leftEye") {
    out_value = HumanoidBone::Bone::LeftEye;
  } else if (type == "rightEye") {
    out_value = HumanoidBone::Bone::RightEye;
  } else if (type == "jaw") {
    out_value = HumanoidBone::Bone::Jaw;
  } else if (type == "leftThumbProximal") {
    out_value = HumanoidBone::Bone::LeftThumbProximal;
  } else if (type == "leftThumbIntermediate") {
    out_value = HumanoidBone::Bone::LeftThumbIntermediate;
  } else if (type == "leftThumbDistal") {
    out_value = HumanoidBone::Bone::LeftThumbDistal;
  } else if (type == "leftIndexProximal") {
    out_value = HumanoidBone::Bone::LeftIndexProximal;
  } else if (type == "leftIndexIntermediate") {
    out_value = HumanoidBone::Bone::LeftIndexIntermediate;
  } else if (type == "leftIndexDistal") {
    out_value = HumanoidBone::Bone::LeftIndexDistal;
  } else if (type == "leftMiddleProximal") {
    out_value = HumanoidBone::Bone::LeftMiddleProximal;
  } else if (type == "leftMiddleIntermediate") {
    out_value = HumanoidBone::Bone::LeftMiddleIntermediate;
  } else if (type == "leftMiddleDistal") {
    out_value = HumanoidBone::Bone::LeftMiddleDistal;
  } else if (type == "leftRingProximal") {
    out_value = HumanoidBone::Bone::LeftRingProximal;
  } else if (type == "leftRingIntermediate") {
    out_value = HumanoidBone::Bone::LeftRingIntermediate;
  } else if (type == "leftRingDistal") {
    out_value = HumanoidBone::Bone::LeftRingDistal;
  } else if (type == "leftLittleProximal") {
    out_value = HumanoidBone::Bone::LeftLittleProximal;
  } else if (type == "leftLittleIntermediate") {
    out_value = HumanoidBone::Bone::LeftLittleIntermediate;
  } else if (type == "leftLittleDistal") {
    out_value = HumanoidBone::Bone::LeftLittleDistal;
  } else if (type == "rightThumbProximal") {
    out_value = HumanoidBone::Bone::RightThumbProximal;
  } else if (type == "rightThumbIntermediate") {
    out_value = HumanoidBone::Bone::RightThumbIntermediate;
  } else if (type == "rightThumbDistal") {
    out_value = HumanoidBone::Bone::RightThumbDistal;
  } else if (type == "rightIndexProximal") {
    out_value = HumanoidBone::Bone::RightIndexProximal;
  } else if (type == "rightIndexIntermediate") {
    out_value = HumanoidBone::Bone::RightIndexIntermediate;
  } else if (type == "rightIndexDistal") {
    out_value = HumanoidBone::Bone::RightIndexDistal;
  } else if (type == "rightMiddleProximal") {
    out_value = HumanoidBone::Bone::RightMiddleProximal;
  } else if (type == "rightMiddleIntermediate") {
    out_value = HumanoidBone::Bone::RightMiddleIntermediate;
  } else if (type == "rightMiddleDistal") {
    out_value = HumanoidBone::Bone::RightMiddleDistal;
  } else if (type == "rightRingProximal") {
    out_value = HumanoidBone::Bone::RightRingProximal;
  } else if (type == "rightRingIntermediate") {
    out_value = HumanoidBone::Bone::RightRingIntermediate;
  } else if (type == "rightRingDistal") {
    out_value = HumanoidBone::Bone::RightRingDistal;
  } else if (type == "rightLittleProximal") {
    out_value = HumanoidBone::Bone::RightLittleProximal;
  } else if (type == "rightLittleIntermediate") {
    out_value = HumanoidBone::Bone::RightLittleIntermediate;
  } else if (type == "rightLittleDistal") {
    out_value = HumanoidBone::Bone::RightLittleDistal;
  } else if (type == "upperChest") {
    out_value = HumanoidBone::Bone::UpperChest;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::AllowedUserName &out_value) {
  std::string type = json.get<std::string>();
  if (type == "OnlyAuthor") {
    out_value = Meta::AllowedUserName::OnlyAuthor;
  } else if (type == "ExplicitlyLicensedPerson") {
    out_value = Meta::AllowedUserName::ExplicitlyLicensedPerson;
  } else if (type == "Everyone") {
    out_value = Meta::AllowedUserName::Everyone;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::ViolentUssageName &out_value) {
  std::string type = json.get<std::string>();
  if (type == "Disallow") {
    out_value = Meta::ViolentUssageName::Disallow;
  } else if (type == "Allow") {
    out_value = Meta::ViolentUssageName::Allow;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::SexualUssageName &out_value) {
  std::string type = json.get<std::string>();
  if (type == "Disallow") {
    out_value = Meta::SexualUssageName::Disallow;
  } else if (type == "Allow") {
    out_value = Meta::SexualUssageName::Allow;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::CommercialUssageName &out_value) {
  std::string type = json.get<std::string>();
  if (type == "Disallow") {
    out_value = Meta::CommercialUssageName::Disallow;
  } else if (type == "Allow") {
    out_value = Meta::CommercialUssageName::Allow;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::LicenseName &out_value) {
  std::string type = json.get<std::string>();
  if (type == "Redistribution_Prohibited") {
    out_value = Meta::LicenseName::Redistribution_Prohibited;
  } else if (type == "CC0") {
    out_value = Meta::LicenseName::CC0;
  } else if (type == "CC_BY") {
    out_value = Meta::LicenseName::CC_BY;
  } else if (type == "CC_BY_NC") {
    out_value = Meta::LicenseName::CC_BY_NC;
  } else if (type == "CC_BY_SA") {
    out_value = Meta::LicenseName::CC_BY_SA;
  } else if (type == "CC_BY_NC_SA") {
    out_value = Meta::LicenseName::CC_BY_NC_SA;
  } else if (type == "CC_BY_ND") {
    out_value = Meta::LicenseName::CC_BY_ND;
  } else if (type == "CC_BY_NC_ND") {
    out_value = Meta::LicenseName::CC_BY_NC_ND;
  } else if (type == "Other") {
    out_value = Meta::LicenseName::Other;
  }
}
inline void to_json(nlohmann::json &json,
                    BlendshapeGroup::PresetName const &in_value) {
  switch (in_value) {
  case BlendshapeGroup::PresetName::Unknown:
    json = "unknown";
    break;
  case BlendshapeGroup::PresetName::Neutral:
    json = "neutral";
    break;
  case BlendshapeGroup::PresetName::A:
    json = "a";
    break;
  case BlendshapeGroup::PresetName::I:
    json = "i";
    break;
  case BlendshapeGroup::PresetName::U:
    json = "u";
    break;
  case BlendshapeGroup::PresetName::E:
    json = "e";
    break;
  case BlendshapeGroup::PresetName::O:
    json = "o";
    break;
  case BlendshapeGroup::PresetName::Blink:
    json = "blink";
    break;
  case BlendshapeGroup::PresetName::Joy:
    json = "joy";
    break;
  case BlendshapeGroup::PresetName::Angry:
    json = "angry";
    break;
  case BlendshapeGroup::PresetName::Sorrow:
    json = "sorrow";
    break;
  case BlendshapeGroup::PresetName::Fun:
    json = "fun";
    break;
  case BlendshapeGroup::PresetName::Lookup:
    json = "lookup";
    break;
  case BlendshapeGroup::PresetName::Lookdown:
    json = "lookdown";
    break;
  case BlendshapeGroup::PresetName::Lookleft:
    json = "lookleft";
    break;
  case BlendshapeGroup::PresetName::Lookright:
    json = "lookright";
    break;
  case BlendshapeGroup::PresetName::Blink_l:
    json = "blink_l";
    break;
  case BlendshapeGroup::PresetName::Blink_r:
    json = "blink_r";
    break;
  default:
    throw std::runtime_error("Unknown PresetName value");
  }
}

inline void to_json(nlohmann::json &json,
                    Firstperson::LookAtTypeName const &in_value) {
  switch (in_value) {
  case Firstperson::LookAtTypeName::Bone:
    json = "Bone";
    break;
  case Firstperson::LookAtTypeName::BlendShape:
    json = "BlendShape";
    break;
  default:
    throw std::runtime_error("Unknown LookAtTypeName value");
  }
}

inline void to_json(nlohmann::json &json, HumanoidBone::Bone const &in_value) {
  switch (in_value) {
  case HumanoidBone::Bone::Hips:
    json = "hips";
    break;
  case HumanoidBone::Bone::LeftUpperLeg:
    json = "leftUpperLeg";
    break;
  case HumanoidBone::Bone::RightUpperLeg:
    json = "rightUpperLeg";
    break;
  case HumanoidBone::Bone::LeftLowerLeg:
    json = "leftLowerLeg";
    break;
  case HumanoidBone::Bone::RightLowerLeg:
    json = "rightLowerLeg";
    break;
  case HumanoidBone::Bone::LeftFoot:
    json = "leftFoot";
    break;
  case HumanoidBone::Bone::RightFoot:
    json = "rightFoot";
    break;
  case HumanoidBone::Bone::Spine:
    json = "spine";
    break;
  case HumanoidBone::Bone::Chest:
    json = "chest";
    break;
  case HumanoidBone::Bone::Neck:
    json = "neck";
    break;
  case HumanoidBone::Bone::Head:
    json = "head";
    break;
  case HumanoidBone::Bone::LeftShoulder:
    json = "leftShoulder";
    break;
  case HumanoidBone::Bone::RightShoulder:
    json = "rightShoulder";
    break;
  case HumanoidBone::Bone::LeftUpperArm:
    json = "leftUpperArm";
    break;
  case HumanoidBone::Bone::RightUpperArm:
    json = "rightUpperArm";
    break;
  case HumanoidBone::Bone::LeftLowerArm:
    json = "leftLowerArm";
    break;
  case HumanoidBone::Bone::RightLowerArm:
    json = "rightLowerArm";
    break;
  case HumanoidBone::Bone::LeftHand:
    json = "leftHand";
    break;
  case HumanoidBone::Bone::RightHand:
    json = "rightHand";
    break;
  case HumanoidBone::Bone::LeftToes:
    json = "leftToes";
    break;
  case HumanoidBone::Bone::RightToes:
    json = "rightToes";
    break;
  case HumanoidBone::Bone::LeftEye:
    json = "leftEye";
    break;
  case HumanoidBone::Bone::RightEye:
    json = "rightEye";
    break;
  case HumanoidBone::Bone::Jaw:
    json = "jaw";
    break;
  case HumanoidBone::Bone::LeftThumbProximal:
    json = "leftThumbProximal";
    break;
  case HumanoidBone::Bone::LeftThumbIntermediate:
    json = "leftThumbIntermediate";
    break;
  case HumanoidBone::Bone::LeftThumbDistal:
    json = "leftThumbDistal";
    break;
  case HumanoidBone::Bone::LeftIndexProximal:
    json = "leftIndexProximal";
    break;
  case HumanoidBone::Bone::LeftIndexIntermediate:
    json = "leftIndexIntermediate";
    break;
  case HumanoidBone::Bone::LeftIndexDistal:
    json = "leftIndexDistal";
    break;
  case HumanoidBone::Bone::LeftMiddleProximal:
    json = "leftMiddleProximal";
    break;
  case HumanoidBone::Bone::LeftMiddleIntermediate:
    json = "leftMiddleIntermediate";
    break;
  case HumanoidBone::Bone::LeftMiddleDistal:
    json = "leftMiddleDistal";
    break;
  case HumanoidBone::Bone::LeftRingProximal:
    json = "leftRingProximal";
    break;
  case HumanoidBone::Bone::LeftRingIntermediate:
    json = "leftRingIntermediate";
    break;
  case HumanoidBone::Bone::LeftRingDistal:
    json = "leftRingDistal";
    break;
  case HumanoidBone::Bone::LeftLittleProximal:
    json = "leftLittleProximal";
    break;
  case HumanoidBone::Bone::LeftLittleIntermediate:
    json = "leftLittleIntermediate";
    break;
  case HumanoidBone::Bone::LeftLittleDistal:
    json = "leftLittleDistal";
    break;
  case HumanoidBone::Bone::RightThumbProximal:
    json = "rightThumbProximal";
    break;
  case HumanoidBone::Bone::RightThumbIntermediate:
    json = "rightThumbIntermediate";
    break;
  case HumanoidBone::Bone::RightThumbDistal:
    json = "rightThumbDistal";
    break;
  case HumanoidBone::Bone::RightIndexProximal:
    json = "rightIndexProximal";
    break;
  case HumanoidBone::Bone::RightIndexIntermediate:
    json = "rightIndexIntermediate";
    break;
  case HumanoidBone::Bone::RightIndexDistal:
    json = "rightIndexDistal";
    break;
  case HumanoidBone::Bone::RightMiddleProximal:
    json = "rightMiddleProximal";
    break;
  case HumanoidBone::Bone::RightMiddleIntermediate:
    json = "rightMiddleIntermediate";
    break;
  case HumanoidBone::Bone::RightMiddleDistal:
    json = "rightMiddleDistal";
    break;
  case HumanoidBone::Bone::RightRingProximal:
    json = "rightRingProximal";
    break;
  case HumanoidBone::Bone::RightRingIntermediate:
    json = "rightRingIntermediate";
    break;
  case HumanoidBone::Bone::RightRingDistal:
    json = "rightRingDistal";
    break;
  case HumanoidBone::Bone::RightLittleProximal:
    json = "rightLittleProximal";
    break;
  case HumanoidBone::Bone::RightLittleIntermediate:
    json = "rightLittleIntermediate";
    break;
  case HumanoidBone::Bone::RightLittleDistal:
    json = "rightLittleDistal";
    break;
  case HumanoidBone::Bone::UpperChest:
    json = "upperChest";
    break;
  default:
    throw std::runtime_error("Unknown Bone value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::AllowedUserName const &in_value) {
  switch (in_value) {
  case Meta::AllowedUserName::OnlyAuthor:
    json = "OnlyAuthor";
    break;
  case Meta::AllowedUserName::ExplicitlyLicensedPerson:
    json = "ExplicitlyLicensedPerson";
    break;
  case Meta::AllowedUserName::Everyone:
    json = "Everyone";
    break;
  default:
    throw std::runtime_error("Unknown AllowedUserName value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::ViolentUssageName const &in_value) {
  switch (in_value) {
  case Meta::ViolentUssageName::Disallow:
    json = "Disallow";
    break;
  case Meta::ViolentUssageName::Allow:
    json = "Allow";
    break;
  default:
    throw std::runtime_error("Unknown ViolentUssageName value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::SexualUssageName const &in_value) {
  switch (in_value) {
  case Meta::SexualUssageName::Disallow:
    json = "Disallow";
    break;
  case Meta::SexualUssageName::Allow:
    json = "Allow";
    break;
  default:
    throw std::runtime_error("Unknown SexualUssageName value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::CommercialUssageName const &in_value) {
  switch (in_value) {
  case Meta::CommercialUssageName::Disallow:
    json = "Disallow";
    break;
  case Meta::CommercialUssageName::Allow:
    json = "Allow";
    break;
  default:
    throw std::runtime_error("Unknown CommercialUssageName value");
  }
}

inline void to_json(nlohmann::json &json, Meta::LicenseName const &in_value) {
  switch (in_value) {
  case Meta::LicenseName::Redistribution_Prohibited:
    json = "Redistribution_Prohibited";
    break;
  case Meta::LicenseName::CC0:
    json = "CC0";
    break;
  case Meta::LicenseName::CC_BY:
    json = "CC_BY";
    break;
  case Meta::LicenseName::CC_BY_NC:
    json = "CC_BY_NC";
    break;
  case Meta::LicenseName::CC_BY_SA:
    json = "CC_BY_SA";
    break;
  case Meta::LicenseName::CC_BY_NC_SA:
    json = "CC_BY_NC_SA";
    break;
  case Meta::LicenseName::CC_BY_ND:
    json = "CC_BY_ND";
    break;
  case Meta::LicenseName::CC_BY_NC_ND:
    json = "CC_BY_NC_ND";
    break;
  case Meta::LicenseName::Other:
    json = "Other";
    break;
  default:
    throw std::runtime_error("Unknown LicenseName value");
  }
}
inline void to_json(nlohmann::json &json,
                    SecondaryanimationSpring const &in_value) {
  VRMC::WriteField("comment", json, in_value.comment, {});
  VRMC::WriteField("stiffiness", json, in_value.stiffiness, 0.f);
  VRMC::WriteField("gravityPower", json, in_value.gravityPower, 0.f);
  VRMC::WriteField("gravityDir", json, in_value.gravityDir);
  VRMC::WriteField("dragForce", json, in_value.dragForce, 0.f);
  VRMC::WriteField("center", json, in_value.center, static_cast<uint32_t>(0));
  VRMC::WriteField("hitRadius", json, in_value.hitRadius, 0.f);
  VRMC::WriteField("bones", json, in_value.bones);
  VRMC::WriteField("colliderGroups", json, in_value.colliderGroups);
}
inline void to_json(nlohmann::json &json,
                    SecondaryanimationCollidergroup const &in_value) {
  VRMC::WriteField("node", json, in_value.node, static_cast<uint32_t>(0));
  VRMC::WriteField("colliders", json, in_value.colliders);
}
inline void to_json(nlohmann::json &json,
                    SecondaryanimationCollidergroup::Collider const &in_value) {
  VRMC::WriteField("offset", json, in_value.offset);
  VRMC::WriteField("radius", json, in_value.radius, 0.f);
}
inline void to_json(nlohmann::json &json, Secondaryanimation const &in_value) {
  VRMC::WriteField("boneGroups", json, in_value.boneGroups);
  VRMC::WriteField("colliderGroups", json, in_value.colliderGroups);
}
inline void to_json(nlohmann::json &json, BlendshapeBind const &in_value) {
  VRMC::WriteField("mesh", json, in_value.mesh, static_cast<uint32_t>(0));
  VRMC::WriteField("index", json, in_value.index, static_cast<uint32_t>(0));
  VRMC::WriteField("weight", json, in_value.weight, 0.f);
}
inline void to_json(nlohmann::json &json,
                    BlendshapeMaterialbind const &in_value) {
  VRMC::WriteField("materialName", json, in_value.materialName, {});
  VRMC::WriteField("propertyName", json, in_value.propertyName, {});
  VRMC::WriteField("targetValue", json, in_value.targetValue);
}
inline void to_json(nlohmann::json &json, BlendshapeGroup const &in_value) {
  VRMC::WriteField("name", json, in_value.name, {});
  VRMC::WriteField("presetName", json, in_value.presetName, {});
  VRMC::WriteField("binds", json, in_value.binds);
  VRMC::WriteField("materialValues", json, in_value.materialValues);
  VRMC::WriteField("isBinary", json, in_value.isBinary, false);
}
inline void to_json(nlohmann::json &json, Blendshape const &in_value) {
  VRMC::WriteField("blendShapeGroups", json, in_value.blendShapeGroups);
}
inline void to_json(nlohmann::json &json,
                    FirstpersonDegreemap const &in_value) {
  VRMC::WriteField("curve", json, in_value.curve);
  VRMC::WriteField("xRange", json, in_value.xRange, 0.f);
  VRMC::WriteField("yRange", json, in_value.yRange, 0.f);
}
inline void to_json(nlohmann::json &json,
                    FirstpersonMeshannotation const &in_value) {
  VRMC::WriteField("mesh", json, in_value.mesh, static_cast<uint32_t>(0));
  VRMC::WriteField("firstPersonFlag", json, in_value.firstPersonFlag, {});
}
inline void to_json(nlohmann::json &json, Firstperson const &in_value) {
  VRMC::WriteField("firstPersonBone", json, in_value.firstPersonBone,
                   static_cast<uint32_t>(0));
  VRMC::WriteField("firstPersonBoneOffset", json,
                   in_value.firstPersonBoneOffset);
  VRMC::WriteField("meshAnnotations", json, in_value.meshAnnotations);
  VRMC::WriteField("lookAtTypeName", json, in_value.lookAtTypeName, {});
  VRMC::WriteField("lookAtHorizontalInner", json,
                   in_value.lookAtHorizontalInner);
  VRMC::WriteField("lookAtHorizontalOuter", json,
                   in_value.lookAtHorizontalOuter);
  VRMC::WriteField("lookAtVerticalDown", json, in_value.lookAtVerticalDown);
  VRMC::WriteField("lookAtVerticalUp", json, in_value.lookAtVerticalUp);
}
inline void to_json(nlohmann::json &json, HumanoidBone const &in_value) {
  VRMC::WriteField("bone", json, in_value.bone, {});
  VRMC::WriteField("node", json, in_value.node, static_cast<uint32_t>(0));
  VRMC::WriteField("useDefaultValues", json, in_value.useDefaultValues, false);
  VRMC::WriteField("min", json, in_value.min);
  VRMC::WriteField("max", json, in_value.max);
  VRMC::WriteField("center", json, in_value.center);
  VRMC::WriteField("axisLength", json, in_value.axisLength, 0.f);
}
inline void to_json(nlohmann::json &json, Humanoid const &in_value) {
  VRMC::WriteField("humanBones", json, in_value.humanBones);
  VRMC::WriteField("armStretch", json, in_value.armStretch, 0.f);
  VRMC::WriteField("legStretch", json, in_value.legStretch, 0.f);
  VRMC::WriteField("upperArmTwist", json, in_value.upperArmTwist, 0.f);
  VRMC::WriteField("lowerArmTwist", json, in_value.lowerArmTwist, 0.f);
  VRMC::WriteField("upperLegTwist", json, in_value.upperLegTwist, 0.f);
  VRMC::WriteField("lowerLegTwist", json, in_value.lowerLegTwist, 0.f);
  VRMC::WriteField("feetSpacing", json, in_value.feetSpacing, 0.f);
  VRMC::WriteField("hasTranslationDoF", json, in_value.hasTranslationDoF,
                   false);
}
inline void to_json(nlohmann::json &json, Material const &in_value) {
  VRMC::WriteField("name", json, in_value.name, {});
  VRMC::WriteField("shader", json, in_value.shader, {});
  VRMC::WriteField("renderQueue", json, in_value.renderQueue,
                   static_cast<uint32_t>(0));
  VRMC::WriteField("floatProperties", json, in_value.floatProperties);
  VRMC::WriteField("vectorProperties", json, in_value.vectorProperties);
  VRMC::WriteField("textureProperties", json, in_value.textureProperties);
  VRMC::WriteField("keywordMap", json, in_value.keywordMap);
  VRMC::WriteField("tagMap", json, in_value.tagMap);
}
inline void to_json(nlohmann::json &json, Meta const &in_value) {
  VRMC::WriteField("title", json, in_value.title, {});
  VRMC::WriteField("version", json, in_value.version, {});
  VRMC::WriteField("author", json, in_value.author, {});
  VRMC::WriteField("contactInformation", json, in_value.contactInformation, {});
  VRMC::WriteField("reference", json, in_value.reference, {});
  VRMC::WriteField("texture", json, in_value.texture, static_cast<uint32_t>(0));
  VRMC::WriteField("allowedUserName", json, in_value.allowedUserName, {});
  VRMC::WriteField("violentUssageName", json, in_value.violentUssageName, {});
  VRMC::WriteField("sexualUssageName", json, in_value.sexualUssageName, {});
  VRMC::WriteField("commercialUssageName", json, in_value.commercialUssageName,
                   {});
  VRMC::WriteField("otherPermissionUrl", json, in_value.otherPermissionUrl, {});
  VRMC::WriteField("licenseName", json, in_value.licenseName, {});
  VRMC::WriteField("otherLicenseUrl", json, in_value.otherLicenseUrl, {});
}
inline void to_json(nlohmann::json &json, Vrm const &in_value) {
  VRMC::WriteField("exporterVersion", json, in_value.exporterVersion, {});
  VRMC::WriteField("specVersion", json, in_value.specVersion, {});
  VRMC::WriteField("meta", json, in_value.meta);
  VRMC::WriteField("humanoid", json, in_value.humanoid);
  VRMC::WriteField("firstPerson", json, in_value.firstPerson);
  VRMC::WriteField("blendShapeMaster", json, in_value.blendShapeMaster);
  VRMC::WriteField("secondaryAnimation", json, in_value.secondaryAnimation);
  VRMC::WriteField("materialProperties", json, in_value.materialProperties);
}
inline void from_json(nlohmann::json const &json,
                      SecondaryanimationSpring &out_value) {
  VRMC::ReadOptionalField("comment", json, out_value.comment);
  VRMC::ReadOptionalField("stiffiness", json, out_value.stiffiness);
  VRMC::ReadOptionalField("gravityPower", json, out_value.gravityPower);
  VRMC::ReadOptionalField("gravityDir", json, out_value.gravityDir);
  VRMC::ReadOptionalField("dragForce", json, out_value.dragForce);
  VRMC::ReadOptionalField("center", json, out_value.center);
  VRMC::ReadOptionalField("hitRadius", json, out_value.hitRadius);
  VRMC::ReadOptionalField("bones", json, out_value.bones);
  VRMC::ReadOptionalField("colliderGroups", json, out_value.colliderGroups);
}
inline void from_json(nlohmann::json const &json,
                      SecondaryanimationCollidergroup &out_value) {
  VRMC::ReadOptionalField("node", json, out_value.node);
  VRMC::ReadOptionalField("colliders", json, out_value.colliders);
}
inline void from_json(nlohmann::json const &json,
                      SecondaryanimationCollidergroup::Collider &out_value) {
  VRMC::ReadOptionalField("offset", json, out_value.offset);
  VRMC::ReadOptionalField("radius", json, out_value.radius);
}
inline void from_json(nlohmann::json const &json,
                      Secondaryanimation &out_value) {
  VRMC::ReadOptionalField("boneGroups", json, out_value.boneGroups);
  VRMC::ReadOptionalField("colliderGroups", json, out_value.colliderGroups);
}
inline void from_json(nlohmann::json const &json, BlendshapeBind &out_value) {
  VRMC::ReadOptionalField("mesh", json, out_value.mesh);
  VRMC::ReadOptionalField("index", json, out_value.index);
  VRMC::ReadOptionalField("weight", json, out_value.weight);
}
inline void from_json(nlohmann::json const &json,
                      BlendshapeMaterialbind &out_value) {
  VRMC::ReadOptionalField("materialName", json, out_value.materialName);
  VRMC::ReadOptionalField("propertyName", json, out_value.propertyName);
  VRMC::ReadOptionalField("targetValue", json, out_value.targetValue);
}
inline void from_json(nlohmann::json const &json, BlendshapeGroup &out_value) {
  VRMC::ReadOptionalField("name", json, out_value.name);
  VRMC::ReadOptionalField("presetName", json, out_value.presetName);
  VRMC::ReadOptionalField("binds", json, out_value.binds);
  VRMC::ReadOptionalField("materialValues", json, out_value.materialValues);
  VRMC::ReadOptionalField("isBinary", json, out_value.isBinary);
}
inline void from_json(nlohmann::json const &json, Blendshape &out_value) {
  VRMC::ReadOptionalField("blendShapeGroups", json, out_value.blendShapeGroups);
}
inline void from_json(nlohmann::json const &json,
                      FirstpersonDegreemap &out_value) {
  VRMC::ReadOptionalField("curve", json, out_value.curve);
  VRMC::ReadOptionalField("xRange", json, out_value.xRange);
  VRMC::ReadOptionalField("yRange", json, out_value.yRange);
}
inline void from_json(nlohmann::json const &json,
                      FirstpersonMeshannotation &out_value) {
  VRMC::ReadOptionalField("mesh", json, out_value.mesh);
  VRMC::ReadOptionalField("firstPersonFlag", json, out_value.firstPersonFlag);
}
inline void from_json(nlohmann::json const &json, Firstperson &out_value) {
  VRMC::ReadOptionalField("firstPersonBone", json, out_value.firstPersonBone);
  VRMC::ReadOptionalField("firstPersonBoneOffset", json,
                          out_value.firstPersonBoneOffset);
  VRMC::ReadOptionalField("meshAnnotations", json, out_value.meshAnnotations);
  VRMC::ReadOptionalField("lookAtTypeName", json, out_value.lookAtTypeName);
  VRMC::ReadOptionalField("lookAtHorizontalInner", json,
                          out_value.lookAtHorizontalInner);
  VRMC::ReadOptionalField("lookAtHorizontalOuter", json,
                          out_value.lookAtHorizontalOuter);
  VRMC::ReadOptionalField("lookAtVerticalDown", json,
                          out_value.lookAtVerticalDown);
  VRMC::ReadOptionalField("lookAtVerticalUp", json, out_value.lookAtVerticalUp);
}
inline void from_json(nlohmann::json const &json, HumanoidBone &out_value) {
  VRMC::ReadOptionalField("bone", json, out_value.bone);
  VRMC::ReadOptionalField("node", json, out_value.node);
  VRMC::ReadOptionalField("useDefaultValues", json, out_value.useDefaultValues);
  VRMC::ReadOptionalField("min", json, out_value.min);
  VRMC::ReadOptionalField("max", json, out_value.max);
  VRMC::ReadOptionalField("center", json, out_value.center);
  VRMC::ReadOptionalField("axisLength", json, out_value.axisLength);
}
inline void from_json(nlohmann::json const &json, Humanoid &out_value) {
  VRMC::ReadOptionalField("humanBones", json, out_value.humanBones);
  VRMC::ReadOptionalField("armStretch", json, out_value.armStretch);
  VRMC::ReadOptionalField("legStretch", json, out_value.legStretch);
  VRMC::ReadOptionalField("upperArmTwist", json, out_value.upperArmTwist);
  VRMC::ReadOptionalField("lowerArmTwist", json, out_value.lowerArmTwist);
  VRMC::ReadOptionalField("upperLegTwist", json, out_value.upperLegTwist);
  VRMC::ReadOptionalField("lowerLegTwist", json, out_value.lowerLegTwist);
  VRMC::ReadOptionalField("feetSpacing", json, out_value.feetSpacing);
  VRMC::ReadOptionalField("hasTranslationDoF", json,
                          out_value.hasTranslationDoF);
}
inline void from_json(nlohmann::json const &json, Material &out_value) {
  VRMC::ReadOptionalField("name", json, out_value.name);
  VRMC::ReadOptionalField("shader", json, out_value.shader);
  VRMC::ReadOptionalField("renderQueue", json, out_value.renderQueue);
  VRMC::ReadOptionalField("floatProperties", json, out_value.floatProperties);
  VRMC::ReadOptionalField("vectorProperties", json, out_value.vectorProperties);
  VRMC::ReadOptionalField("textureProperties", json,
                          out_value.textureProperties);
  VRMC::ReadOptionalField("keywordMap", json, out_value.keywordMap);
  VRMC::ReadOptionalField("tagMap", json, out_value.tagMap);
}
inline void from_json(nlohmann::json const &json, Meta &out_value) {
  VRMC::ReadOptionalField("title", json, out_value.title);
  VRMC::ReadOptionalField("version", json, out_value.version);
  VRMC::ReadOptionalField("author", json, out_value.author);
  VRMC::ReadOptionalField("contactInformation", json,
                          out_value.contactInformation);
  VRMC::ReadOptionalField("reference", json, out_value.reference);
  VRMC::ReadOptionalField("texture", json, out_value.texture);
  VRMC::ReadOptionalField("allowedUserName", json, out_value.allowedUserName);
  VRMC::ReadOptionalField("violentUssageName", json,
                          out_value.violentUssageName);
  VRMC::ReadOptionalField("sexualUssageName", json, out_value.sexualUssageName);
  VRMC::ReadOptionalField("commercialUssageName", json,
                          out_value.commercialUssageName);
  VRMC::ReadOptionalField("otherPermissionUrl", json,
                          out_value.otherPermissionUrl);
  VRMC::ReadOptionalField("licenseName", json, out_value.licenseName);
  VRMC::ReadOptionalField("otherLicenseUrl", json, out_value.otherLicenseUrl);
}
inline void from_json(nlohmann::json const &json, Vrm &out_value) {
  VRMC::ReadOptionalField("exporterVersion", json, out_value.exporterVersion);
  VRMC::ReadOptionalField("specVersion", json, out_value.specVersion);
  VRMC::ReadOptionalField("meta", json, out_value.meta);
  VRMC::ReadOptionalField("humanoid", json, out_value.humanoid);
  VRMC::ReadOptionalField("firstPerson", json, out_value.firstPerson);
  VRMC::ReadOptionalField("blendShapeMaster", json, out_value.blendShapeMaster);
  VRMC::ReadOptionalField("secondaryAnimation", json,
                          out_value.secondaryAnimation);
  VRMC::ReadOptionalField("materialProperties", json,
                          out_value.materialProperties);
}
} // namespace VRMC_VRM_0_0
#endif

#ifdef USE_VRMC_VRM_1_0

namespace VRMC_VRM_1_0 {
struct TextureInfo {
  uint32_t index{};
  uint32_t texCoord{};
};

struct ShadingShiftTextureInfo {
  uint32_t index{};
  uint32_t texCoord{};
  float scale = 1.f;
};

struct ColliderGroup {
  std::string name;
  std::vector<uint32_t> colliders{};
};

struct SpringBoneJoint {
  uint32_t node{};
  float hitRadius{};
  float stiffness = 1.f;
  float gravityPower{};
  std::vector<float> gravityDir = {0, -1, 0};
  float dragForce = 0.5f;
};

struct ColliderShape {
  struct Sphere {
    std::vector<float> offset = {0, 0, 0};
    float radius{};
  };

  Sphere sphere{};
  struct Capsule {
    std::vector<float> offset = {0, 0, 0};
    float radius{};
    std::vector<float> tail = {0, 0, 0};
  };

  Capsule capsule{};
};

struct MaterialColorBind {
  uint32_t material{};
  enum class MaterialColorType : uint8_t {
    Color,
    EmissionColor,
    ShadeColor,
    RimColor,
    OutlineColor
  };
  MaterialColorType type;
  std::vector<float> targetValue{};
};

struct MorphTargetBind {
  uint32_t node{};
  uint32_t index{};
  float weight{};
};

struct TextureTransformBind {
  uint32_t material{};
  std::vector<float> scale = {1, 1};
  std::vector<float> offset = {0, 0};
};

struct MeshAnnotation {
  uint32_t node{};
  enum class FirstPersonType : uint8_t {
    Auto,
    Both,
    ThirdPersonOnly,
    FirstPersonOnly
  };
  FirstPersonType type;
};

struct HumanBone {
  uint32_t node{};
};

struct LookAtRangeMap {
  float inputMaxValue{};
  float outputScale{};
};

struct Meta {
  std::string name;
  std::string version;
  std::vector<std::string> authors{};
  std::string copyrightInformation;
  std::string contactInformation;
  std::vector<std::string> references{};
  std::string thirdPartyLicenses;
  uint32_t thumbnailImage{};
  std::string licenseUrl;
  enum class AvatarPermissionType : uint8_t {
    OnlyAuthor,
    OnlySeparatelyLicensedPerson,
    Everyone
  };
  AvatarPermissionType avatarPermission = AvatarPermissionType::OnlyAuthor;
  bool allowExcessivelyViolentUsage{};
  bool allowExcessivelySexualUsage{};
  enum class CommercialUsageType : uint8_t {
    PersonalNonProfit,
    PersonalProfit,
    Corporation
  };
  CommercialUsageType commercialUsage = CommercialUsageType::PersonalNonProfit;
  bool allowPoliticalOrReligiousUsage{};
  bool allowAntisocialOrHateUsage{};
  enum class CreditNotationType : uint8_t { Required, Unnecessary };
  CreditNotationType creditNotation = CreditNotationType::Required;
  bool allowRedistribution{};
  enum class ModificationType : uint8_t {
    Prohibited,
    AllowModification,
    AllowModificationRedistribution
  };
  ModificationType modification = ModificationType::Prohibited;
  std::string otherLicenseUrl;
};

struct AimConstraint {
  uint32_t source{};
  enum class AimAxis : uint8_t {
    PositiveX,
    NegativeX,
    PositiveY,
    NegativeY,
    PositiveZ,
    NegativeZ
  };
  AimAxis aimAxis;
  float weight = 1.f;
};

struct RollConstraint {
  uint32_t source{};
  enum class RollAxis : uint8_t { X, Y, Z };
  RollAxis rollAxis;
  float weight = 1.f;
};

struct RotationConstraint {
  uint32_t source{};
  float weight = 1.f;
};

struct Collider {
  uint32_t node{};
  ColliderShape shape{};
};

struct Spring {
  std::string name;
  std::vector<SpringBoneJoint> joints{};
  std::vector<uint32_t> colliderGroups{};
  uint32_t center{};
};

struct HumanBones {
  HumanBone hips{};
  HumanBone spine{};
  HumanBone chest{};
  HumanBone upperChest{};
  HumanBone neck{};
  HumanBone head{};
  HumanBone leftEye{};
  HumanBone rightEye{};
  HumanBone jaw{};
  HumanBone leftUpperLeg{};
  HumanBone leftLowerLeg{};
  HumanBone leftFoot{};
  HumanBone leftToes{};
  HumanBone rightUpperLeg{};
  HumanBone rightLowerLeg{};
  HumanBone rightFoot{};
  HumanBone rightToes{};
  HumanBone leftShoulder{};
  HumanBone leftUpperArm{};
  HumanBone leftLowerArm{};
  HumanBone leftHand{};
  HumanBone rightShoulder{};
  HumanBone rightUpperArm{};
  HumanBone rightLowerArm{};
  HumanBone rightHand{};
  HumanBone leftThumbProximal{};
  HumanBone leftThumbIntermediate{};
  HumanBone leftThumbDistal{};
  HumanBone leftIndexProximal{};
  HumanBone leftIndexIntermediate{};
  HumanBone leftIndexDistal{};
  HumanBone leftMiddleProximal{};
  HumanBone leftMiddleIntermediate{};
  HumanBone leftMiddleDistal{};
  HumanBone leftRingProximal{};
  HumanBone leftRingIntermediate{};
  HumanBone leftRingDistal{};
  HumanBone leftLittleProximal{};
  HumanBone leftLittleIntermediate{};
  HumanBone leftLittleDistal{};
  HumanBone rightThumbProximal{};
  HumanBone rightThumbIntermediate{};
  HumanBone rightThumbDistal{};
  HumanBone rightIndexProximal{};
  HumanBone rightIndexIntermediate{};
  HumanBone rightIndexDistal{};
  HumanBone rightMiddleProximal{};
  HumanBone rightMiddleIntermediate{};
  HumanBone rightMiddleDistal{};
  HumanBone rightRingProximal{};
  HumanBone rightRingIntermediate{};
  HumanBone rightRingDistal{};
  HumanBone rightLittleProximal{};
  HumanBone rightLittleIntermediate{};
  HumanBone rightLittleDistal{};
};

struct Constraint {
  RollConstraint roll{};
  AimConstraint aim{};
  RotationConstraint rotation{};
};

struct SpringBone {
  std::string specVersion;
  std::vector<Collider> colliders{};
  std::vector<ColliderGroup> colliderGroups{};
  std::vector<Spring> springs{};
};

struct Expression {
  std::vector<MorphTargetBind> morphTargetBinds{};
  std::vector<MaterialColorBind> materialColorBinds{};
  std::vector<TextureTransformBind> textureTransformBinds{};
  bool isBinary{};
  enum class ExpressionOverrideType : uint8_t { None, Block, Blend };
  ExpressionOverrideType overrideBlink = ExpressionOverrideType::None;
  ExpressionOverrideType overrideLookAt = ExpressionOverrideType::None;
  ExpressionOverrideType overrideMouth = ExpressionOverrideType::None;
};

struct Expressions {
  struct Preset {
    Expression happy{};
    Expression angry{};
    Expression sad{};
    Expression relaxed{};
    Expression surprised{};
    Expression aa{};
    Expression ih{};
    Expression ou{};
    Expression ee{};
    Expression oh{};
    Expression blink{};
    Expression blinkLeft{};
    Expression blinkRight{};
    Expression lookUp{};
    Expression lookDown{};
    Expression lookLeft{};
    Expression lookRight{};
    Expression neutral{};
  };

  Preset preset{};
  Expression custom{};
};

struct FirstPerson {
  std::vector<MeshAnnotation> meshAnnotations{};
};

struct Humanoid {
  HumanBones humanBones{};
};

struct LookAt {
  std::vector<float> offsetFromHeadBone{};
  enum class LookAtType : uint8_t { Bone, Expression };
  LookAtType type;
  LookAtRangeMap rangeMapHorizontalInner{};
  LookAtRangeMap rangeMapHorizontalOuter{};
  LookAtRangeMap rangeMapVerticalDown{};
  LookAtRangeMap rangeMapVerticalUp{};
};

struct MaterialsHdrEmissiveMultiplier {
  float emissiveMultiplier = 1.f;
};

struct MaterialsMtoon {
  std::string specVersion;
  bool transparentWithZWrite{};
  uint32_t renderQueueOffsetNumber{};
  std::vector<float> shadeColorFactor = {1, 1, 1};
  TextureInfo shadeMultiplyTexture{};
  float shadingShiftFactor{};
  ShadingShiftTextureInfo shadingShiftTexture{};
  float shadingToonyFactor = 0.9f;
  float giEqualizationFactor = 0.9f;
  std::vector<float> matcapFactor = {1, 1, 1};
  TextureInfo matcapTexture{};
  std::vector<float> parametricRimColorFactor = {0, 0, 0};
  TextureInfo rimMultiplyTexture{};
  float rimLightingMixFactor{};
  float parametricRimFresnelPowerFactor = 1.f;
  float parametricRimLiftFactor{};
  enum class OutlineWidthMode : uint8_t {
    None,
    WorldCoordinates,
    ScreenCoordinates
  };
  OutlineWidthMode outlineWidthMode = OutlineWidthMode::None;
  float outlineWidthFactor{};
  TextureInfo outlineWidthMultiplyTexture{};
  std::vector<float> outlineColorFactor = {0, 0, 0};
  float outlineLightingMixFactor = 1.f;
  TextureInfo uvAnimationMaskTexture{};
  float uvAnimationScrollXSpeedFactor{};
  float uvAnimationScrollYSpeedFactor{};
  float uvAnimationRotationSpeedFactor{};
};

struct NodeConstraintextension {
  std::string specVersion;
  Constraint constraint{};
};

struct Vrm {
  std::string specVersion;
  Meta meta{};
  Humanoid humanoid{};
  FirstPerson firstPerson{};
  LookAt lookAt{};
  Expressions expressions{};
};
inline void from_json(nlohmann::json const &json,
                      MaterialColorBind::MaterialColorType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "color") {
    out_value = MaterialColorBind::MaterialColorType::Color;
  } else if (type == "emissionColor") {
    out_value = MaterialColorBind::MaterialColorType::EmissionColor;
  } else if (type == "shadeColor") {
    out_value = MaterialColorBind::MaterialColorType::ShadeColor;
  } else if (type == "rimColor") {
    out_value = MaterialColorBind::MaterialColorType::RimColor;
  } else if (type == "outlineColor") {
    out_value = MaterialColorBind::MaterialColorType::OutlineColor;
  }
}

inline void from_json(nlohmann::json const &json,
                      MeshAnnotation::FirstPersonType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "auto") {
    out_value = MeshAnnotation::FirstPersonType::Auto;
  } else if (type == "both") {
    out_value = MeshAnnotation::FirstPersonType::Both;
  } else if (type == "thirdPersonOnly") {
    out_value = MeshAnnotation::FirstPersonType::ThirdPersonOnly;
  } else if (type == "firstPersonOnly") {
    out_value = MeshAnnotation::FirstPersonType::FirstPersonOnly;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::AvatarPermissionType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "onlyAuthor") {
    out_value = Meta::AvatarPermissionType::OnlyAuthor;
  } else if (type == "onlySeparatelyLicensedPerson") {
    out_value = Meta::AvatarPermissionType::OnlySeparatelyLicensedPerson;
  } else if (type == "everyone") {
    out_value = Meta::AvatarPermissionType::Everyone;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::CommercialUsageType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "personalNonProfit") {
    out_value = Meta::CommercialUsageType::PersonalNonProfit;
  } else if (type == "personalProfit") {
    out_value = Meta::CommercialUsageType::PersonalProfit;
  } else if (type == "corporation") {
    out_value = Meta::CommercialUsageType::Corporation;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::CreditNotationType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "required") {
    out_value = Meta::CreditNotationType::Required;
  } else if (type == "unnecessary") {
    out_value = Meta::CreditNotationType::Unnecessary;
  }
}

inline void from_json(nlohmann::json const &json,
                      Meta::ModificationType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "prohibited") {
    out_value = Meta::ModificationType::Prohibited;
  } else if (type == "allowModification") {
    out_value = Meta::ModificationType::AllowModification;
  } else if (type == "allowModificationRedistribution") {
    out_value = Meta::ModificationType::AllowModificationRedistribution;
  }
}

inline void from_json(nlohmann::json const &json,
                      AimConstraint::AimAxis &out_value) {
  std::string type = json.get<std::string>();
  if (type == "PositiveX") {
    out_value = AimConstraint::AimAxis::PositiveX;
  } else if (type == "NegativeX") {
    out_value = AimConstraint::AimAxis::NegativeX;
  } else if (type == "PositiveY") {
    out_value = AimConstraint::AimAxis::PositiveY;
  } else if (type == "NegativeY") {
    out_value = AimConstraint::AimAxis::NegativeY;
  } else if (type == "PositiveZ") {
    out_value = AimConstraint::AimAxis::PositiveZ;
  } else if (type == "NegativeZ") {
    out_value = AimConstraint::AimAxis::NegativeZ;
  }
}

inline void from_json(nlohmann::json const &json,
                      RollConstraint::RollAxis &out_value) {
  std::string type = json.get<std::string>();
  if (type == "X") {
    out_value = RollConstraint::RollAxis::X;
  } else if (type == "Y") {
    out_value = RollConstraint::RollAxis::Y;
  } else if (type == "Z") {
    out_value = RollConstraint::RollAxis::Z;
  }
}

inline void from_json(nlohmann::json const &json,
                      Expression::ExpressionOverrideType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "none") {
    out_value = Expression::ExpressionOverrideType::None;
  } else if (type == "block") {
    out_value = Expression::ExpressionOverrideType::Block;
  } else if (type == "blend") {
    out_value = Expression::ExpressionOverrideType::Blend;
  }
}

inline void from_json(nlohmann::json const &json,
                      LookAt::LookAtType &out_value) {
  std::string type = json.get<std::string>();
  if (type == "bone") {
    out_value = LookAt::LookAtType::Bone;
  } else if (type == "expression") {
    out_value = LookAt::LookAtType::Expression;
  }
}

inline void from_json(nlohmann::json const &json,
                      MaterialsMtoon::OutlineWidthMode &out_value) {
  std::string type = json.get<std::string>();
  if (type == "none") {
    out_value = MaterialsMtoon::OutlineWidthMode::None;
  } else if (type == "worldCoordinates") {
    out_value = MaterialsMtoon::OutlineWidthMode::WorldCoordinates;
  } else if (type == "screenCoordinates") {
    out_value = MaterialsMtoon::OutlineWidthMode::ScreenCoordinates;
  }
}
inline void to_json(nlohmann::json &json,
                    MaterialColorBind::MaterialColorType const &in_value) {
  switch (in_value) {
  case MaterialColorBind::MaterialColorType::Color:
    json = "color";
    break;
  case MaterialColorBind::MaterialColorType::EmissionColor:
    json = "emissionColor";
    break;
  case MaterialColorBind::MaterialColorType::ShadeColor:
    json = "shadeColor";
    break;
  case MaterialColorBind::MaterialColorType::RimColor:
    json = "rimColor";
    break;
  case MaterialColorBind::MaterialColorType::OutlineColor:
    json = "outlineColor";
    break;
  default:
    throw std::runtime_error("Unknown MaterialColorType value");
  }
}

inline void to_json(nlohmann::json &json,
                    MeshAnnotation::FirstPersonType const &in_value) {
  switch (in_value) {
  case MeshAnnotation::FirstPersonType::Auto:
    json = "auto";
    break;
  case MeshAnnotation::FirstPersonType::Both:
    json = "both";
    break;
  case MeshAnnotation::FirstPersonType::ThirdPersonOnly:
    json = "thirdPersonOnly";
    break;
  case MeshAnnotation::FirstPersonType::FirstPersonOnly:
    json = "firstPersonOnly";
    break;
  default:
    throw std::runtime_error("Unknown FirstPersonType value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::AvatarPermissionType const &in_value) {
  switch (in_value) {
  case Meta::AvatarPermissionType::OnlyAuthor:
    json = "onlyAuthor";
    break;
  case Meta::AvatarPermissionType::OnlySeparatelyLicensedPerson:
    json = "onlySeparatelyLicensedPerson";
    break;
  case Meta::AvatarPermissionType::Everyone:
    json = "everyone";
    break;
  default:
    throw std::runtime_error("Unknown AvatarPermissionType value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::CommercialUsageType const &in_value) {
  switch (in_value) {
  case Meta::CommercialUsageType::PersonalNonProfit:
    json = "personalNonProfit";
    break;
  case Meta::CommercialUsageType::PersonalProfit:
    json = "personalProfit";
    break;
  case Meta::CommercialUsageType::Corporation:
    json = "corporation";
    break;
  default:
    throw std::runtime_error("Unknown CommercialUsageType value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::CreditNotationType const &in_value) {
  switch (in_value) {
  case Meta::CreditNotationType::Required:
    json = "required";
    break;
  case Meta::CreditNotationType::Unnecessary:
    json = "unnecessary";
    break;
  default:
    throw std::runtime_error("Unknown CreditNotationType value");
  }
}

inline void to_json(nlohmann::json &json,
                    Meta::ModificationType const &in_value) {
  switch (in_value) {
  case Meta::ModificationType::Prohibited:
    json = "prohibited";
    break;
  case Meta::ModificationType::AllowModification:
    json = "allowModification";
    break;
  case Meta::ModificationType::AllowModificationRedistribution:
    json = "allowModificationRedistribution";
    break;
  default:
    throw std::runtime_error("Unknown ModificationType value");
  }
}

inline void to_json(nlohmann::json &json,
                    AimConstraint::AimAxis const &in_value) {
  switch (in_value) {
  case AimConstraint::AimAxis::PositiveX:
    json = "PositiveX";
    break;
  case AimConstraint::AimAxis::NegativeX:
    json = "NegativeX";
    break;
  case AimConstraint::AimAxis::PositiveY:
    json = "PositiveY";
    break;
  case AimConstraint::AimAxis::NegativeY:
    json = "NegativeY";
    break;
  case AimConstraint::AimAxis::PositiveZ:
    json = "PositiveZ";
    break;
  case AimConstraint::AimAxis::NegativeZ:
    json = "NegativeZ";
    break;
  default:
    throw std::runtime_error("Unknown AimAxis value");
  }
}

inline void to_json(nlohmann::json &json,
                    RollConstraint::RollAxis const &in_value) {
  switch (in_value) {
  case RollConstraint::RollAxis::X:
    json = "X";
    break;
  case RollConstraint::RollAxis::Y:
    json = "Y";
    break;
  case RollConstraint::RollAxis::Z:
    json = "Z";
    break;
  default:
    throw std::runtime_error("Unknown RollAxis value");
  }
}

inline void to_json(nlohmann::json &json,
                    Expression::ExpressionOverrideType const &in_value) {
  switch (in_value) {
  case Expression::ExpressionOverrideType::None:
    json = "none";
    break;
  case Expression::ExpressionOverrideType::Block:
    json = "block";
    break;
  case Expression::ExpressionOverrideType::Blend:
    json = "blend";
    break;
  default:
    throw std::runtime_error("Unknown ExpressionOverrideType value");
  }
}

inline void to_json(nlohmann::json &json, LookAt::LookAtType const &in_value) {
  switch (in_value) {
  case LookAt::LookAtType::Bone:
    json = "bone";
    break;
  case LookAt::LookAtType::Expression:
    json = "expression";
    break;
  default:
    throw std::runtime_error("Unknown LookAtType value");
  }
}

inline void to_json(nlohmann::json &json,
                    MaterialsMtoon::OutlineWidthMode const &in_value) {
  switch (in_value) {
  case MaterialsMtoon::OutlineWidthMode::None:
    json = "none";
    break;
  case MaterialsMtoon::OutlineWidthMode::WorldCoordinates:
    json = "worldCoordinates";
    break;
  case MaterialsMtoon::OutlineWidthMode::ScreenCoordinates:
    json = "screenCoordinates";
    break;
  default:
    throw std::runtime_error("Unknown OutlineWidthMode value");
  }
}
inline void to_json(nlohmann::json &json, TextureInfo const &in_value) {
  VRMC::WriteField("index", json, in_value.index, static_cast<uint32_t>(0));
  VRMC::WriteField("texCoord", json, in_value.texCoord,
                   static_cast<uint32_t>(0));
}
inline void to_json(nlohmann::json &json,
                    ShadingShiftTextureInfo const &in_value) {
  VRMC::WriteField("index", json, in_value.index, static_cast<uint32_t>(0));
  VRMC::WriteField("texCoord", json, in_value.texCoord,
                   static_cast<uint32_t>(0));
  VRMC::WriteField("scale", json, in_value.scale, 1.f);
}
inline void to_json(nlohmann::json &json, ColliderGroup const &in_value) {
  VRMC::WriteField("name", json, in_value.name, {});
  VRMC::WriteField("colliders", json, in_value.colliders);
}
inline void to_json(nlohmann::json &json, SpringBoneJoint const &in_value) {
  VRMC::WriteField("node", json, in_value.node, static_cast<uint32_t>(0));
  VRMC::WriteField("hitRadius", json, in_value.hitRadius, 0.f);
  VRMC::WriteField("stiffness", json, in_value.stiffness, 1.f);
  VRMC::WriteField("gravityPower", json, in_value.gravityPower, 0.f);
  VRMC::WriteField("gravityDir", json, in_value.gravityDir, {0, -1, 0});
  VRMC::WriteField("dragForce", json, in_value.dragForce, 0.5f);
}
inline void to_json(nlohmann::json &json, ColliderShape const &in_value) {
  VRMC::WriteField("sphere", json, in_value.sphere);
  VRMC::WriteField("capsule", json, in_value.capsule);
}
inline void to_json(nlohmann::json &json,
                    ColliderShape::Sphere const &in_value) {
  VRMC::WriteField("offset", json, in_value.offset, {0, 0, 0});
  VRMC::WriteField("radius", json, in_value.radius, 0.f);
}
inline void to_json(nlohmann::json &json,
                    ColliderShape::Capsule const &in_value) {
  VRMC::WriteField("offset", json, in_value.offset, {0, 0, 0});
  VRMC::WriteField("radius", json, in_value.radius, 0.f);
  VRMC::WriteField("tail", json, in_value.tail, {0, 0, 0});
}
inline void to_json(nlohmann::json &json, MaterialColorBind const &in_value) {
  VRMC::WriteField("material", json, in_value.material,
                   static_cast<uint32_t>(0));
  VRMC::WriteField("type", json, in_value.type, {});
  VRMC::WriteField("targetValue", json, in_value.targetValue);
}
inline void to_json(nlohmann::json &json, MorphTargetBind const &in_value) {
  VRMC::WriteField("node", json, in_value.node, static_cast<uint32_t>(0));
  VRMC::WriteField("index", json, in_value.index, static_cast<uint32_t>(0));
  VRMC::WriteField("weight", json, in_value.weight, 0.f);
}
inline void to_json(nlohmann::json &json,
                    TextureTransformBind const &in_value) {
  VRMC::WriteField("material", json, in_value.material,
                   static_cast<uint32_t>(0));
  VRMC::WriteField("scale", json, in_value.scale, {1, 1});
  VRMC::WriteField("offset", json, in_value.offset, {0, 0});
}
inline void to_json(nlohmann::json &json, MeshAnnotation const &in_value) {
  VRMC::WriteField("node", json, in_value.node, static_cast<uint32_t>(0));
  VRMC::WriteField("type", json, in_value.type, {});
}
inline void to_json(nlohmann::json &json, HumanBone const &in_value) {
  VRMC::WriteField("node", json, in_value.node, static_cast<uint32_t>(0));
}
inline void to_json(nlohmann::json &json, LookAtRangeMap const &in_value) {
  VRMC::WriteField("inputMaxValue", json, in_value.inputMaxValue, 0.f);
  VRMC::WriteField("outputScale", json, in_value.outputScale, 0.f);
}
inline void to_json(nlohmann::json &json, Meta const &in_value) {
  VRMC::WriteField("name", json, in_value.name, {});
  VRMC::WriteField("version", json, in_value.version, {});
  VRMC::WriteField("authors", json, in_value.authors);
  VRMC::WriteField("copyrightInformation", json, in_value.copyrightInformation,
                   {});
  VRMC::WriteField("contactInformation", json, in_value.contactInformation, {});
  VRMC::WriteField("references", json, in_value.references);
  VRMC::WriteField("thirdPartyLicenses", json, in_value.thirdPartyLicenses, {});
  VRMC::WriteField("thumbnailImage", json, in_value.thumbnailImage,
                   static_cast<uint32_t>(0));
  VRMC::WriteField("licenseUrl", json, in_value.licenseUrl, {});
  VRMC::WriteField("avatarPermission", json, in_value.avatarPermission,
                   Meta::AvatarPermissionType::OnlyAuthor);
  VRMC::WriteField("allowExcessivelyViolentUsage", json,
                   in_value.allowExcessivelyViolentUsage, false);
  VRMC::WriteField("allowExcessivelySexualUsage", json,
                   in_value.allowExcessivelySexualUsage, false);
  VRMC::WriteField("commercialUsage", json, in_value.commercialUsage,
                   Meta::CommercialUsageType::PersonalNonProfit);
  VRMC::WriteField("allowPoliticalOrReligiousUsage", json,
                   in_value.allowPoliticalOrReligiousUsage, false);
  VRMC::WriteField("allowAntisocialOrHateUsage", json,
                   in_value.allowAntisocialOrHateUsage, false);
  VRMC::WriteField("creditNotation", json, in_value.creditNotation,
                   Meta::CreditNotationType::Required);
  VRMC::WriteField("allowRedistribution", json, in_value.allowRedistribution,
                   false);
  VRMC::WriteField("modification", json, in_value.modification,
                   Meta::ModificationType::Prohibited);
  VRMC::WriteField("otherLicenseUrl", json, in_value.otherLicenseUrl, {});
}
inline void to_json(nlohmann::json &json, AimConstraint const &in_value) {
  VRMC::WriteField("source", json, in_value.source, static_cast<uint32_t>(0));
  VRMC::WriteField("aimAxis", json, in_value.aimAxis, {});
  VRMC::WriteField("weight", json, in_value.weight, 1.f);
}
inline void to_json(nlohmann::json &json, RollConstraint const &in_value) {
  VRMC::WriteField("source", json, in_value.source, static_cast<uint32_t>(0));
  VRMC::WriteField("rollAxis", json, in_value.rollAxis, {});
  VRMC::WriteField("weight", json, in_value.weight, 1.f);
}
inline void to_json(nlohmann::json &json, RotationConstraint const &in_value) {
  VRMC::WriteField("source", json, in_value.source, static_cast<uint32_t>(0));
  VRMC::WriteField("weight", json, in_value.weight, 1.f);
}
inline void to_json(nlohmann::json &json, Collider const &in_value) {
  VRMC::WriteField("node", json, in_value.node, static_cast<uint32_t>(0));
  VRMC::WriteField("shape", json, in_value.shape);
}
inline void to_json(nlohmann::json &json, Spring const &in_value) {
  VRMC::WriteField("name", json, in_value.name, {});
  VRMC::WriteField("joints", json, in_value.joints);
  VRMC::WriteField("colliderGroups", json, in_value.colliderGroups);
  VRMC::WriteField("center", json, in_value.center, static_cast<uint32_t>(0));
}
inline void to_json(nlohmann::json &json, HumanBones const &in_value) {
  VRMC::WriteField("hips", json, in_value.hips);
  VRMC::WriteField("spine", json, in_value.spine);
  VRMC::WriteField("chest", json, in_value.chest);
  VRMC::WriteField("upperChest", json, in_value.upperChest);
  VRMC::WriteField("neck", json, in_value.neck);
  VRMC::WriteField("head", json, in_value.head);
  VRMC::WriteField("leftEye", json, in_value.leftEye);
  VRMC::WriteField("rightEye", json, in_value.rightEye);
  VRMC::WriteField("jaw", json, in_value.jaw);
  VRMC::WriteField("leftUpperLeg", json, in_value.leftUpperLeg);
  VRMC::WriteField("leftLowerLeg", json, in_value.leftLowerLeg);
  VRMC::WriteField("leftFoot", json, in_value.leftFoot);
  VRMC::WriteField("leftToes", json, in_value.leftToes);
  VRMC::WriteField("rightUpperLeg", json, in_value.rightUpperLeg);
  VRMC::WriteField("rightLowerLeg", json, in_value.rightLowerLeg);
  VRMC::WriteField("rightFoot", json, in_value.rightFoot);
  VRMC::WriteField("rightToes", json, in_value.rightToes);
  VRMC::WriteField("leftShoulder", json, in_value.leftShoulder);
  VRMC::WriteField("leftUpperArm", json, in_value.leftUpperArm);
  VRMC::WriteField("leftLowerArm", json, in_value.leftLowerArm);
  VRMC::WriteField("leftHand", json, in_value.leftHand);
  VRMC::WriteField("rightShoulder", json, in_value.rightShoulder);
  VRMC::WriteField("rightUpperArm", json, in_value.rightUpperArm);
  VRMC::WriteField("rightLowerArm", json, in_value.rightLowerArm);
  VRMC::WriteField("rightHand", json, in_value.rightHand);
  VRMC::WriteField("leftThumbProximal", json, in_value.leftThumbProximal);
  VRMC::WriteField("leftThumbIntermediate", json,
                   in_value.leftThumbIntermediate);
  VRMC::WriteField("leftThumbDistal", json, in_value.leftThumbDistal);
  VRMC::WriteField("leftIndexProximal", json, in_value.leftIndexProximal);
  VRMC::WriteField("leftIndexIntermediate", json,
                   in_value.leftIndexIntermediate);
  VRMC::WriteField("leftIndexDistal", json, in_value.leftIndexDistal);
  VRMC::WriteField("leftMiddleProximal", json, in_value.leftMiddleProximal);
  VRMC::WriteField("leftMiddleIntermediate", json,
                   in_value.leftMiddleIntermediate);
  VRMC::WriteField("leftMiddleDistal", json, in_value.leftMiddleDistal);
  VRMC::WriteField("leftRingProximal", json, in_value.leftRingProximal);
  VRMC::WriteField("leftRingIntermediate", json, in_value.leftRingIntermediate);
  VRMC::WriteField("leftRingDistal", json, in_value.leftRingDistal);
  VRMC::WriteField("leftLittleProximal", json, in_value.leftLittleProximal);
  VRMC::WriteField("leftLittleIntermediate", json,
                   in_value.leftLittleIntermediate);
  VRMC::WriteField("leftLittleDistal", json, in_value.leftLittleDistal);
  VRMC::WriteField("rightThumbProximal", json, in_value.rightThumbProximal);
  VRMC::WriteField("rightThumbIntermediate", json,
                   in_value.rightThumbIntermediate);
  VRMC::WriteField("rightThumbDistal", json, in_value.rightThumbDistal);
  VRMC::WriteField("rightIndexProximal", json, in_value.rightIndexProximal);
  VRMC::WriteField("rightIndexIntermediate", json,
                   in_value.rightIndexIntermediate);
  VRMC::WriteField("rightIndexDistal", json, in_value.rightIndexDistal);
  VRMC::WriteField("rightMiddleProximal", json, in_value.rightMiddleProximal);
  VRMC::WriteField("rightMiddleIntermediate", json,
                   in_value.rightMiddleIntermediate);
  VRMC::WriteField("rightMiddleDistal", json, in_value.rightMiddleDistal);
  VRMC::WriteField("rightRingProximal", json, in_value.rightRingProximal);
  VRMC::WriteField("rightRingIntermediate", json,
                   in_value.rightRingIntermediate);
  VRMC::WriteField("rightRingDistal", json, in_value.rightRingDistal);
  VRMC::WriteField("rightLittleProximal", json, in_value.rightLittleProximal);
  VRMC::WriteField("rightLittleIntermediate", json,
                   in_value.rightLittleIntermediate);
  VRMC::WriteField("rightLittleDistal", json, in_value.rightLittleDistal);
}
inline void to_json(nlohmann::json &json, Constraint const &in_value) {
  VRMC::WriteField("roll", json, in_value.roll);
  VRMC::WriteField("aim", json, in_value.aim);
  VRMC::WriteField("rotation", json, in_value.rotation);
}
inline void to_json(nlohmann::json &json, SpringBone const &in_value) {
  VRMC::WriteField("specVersion", json, in_value.specVersion, {});
  VRMC::WriteField("colliders", json, in_value.colliders);
  VRMC::WriteField("colliderGroups", json, in_value.colliderGroups);
  VRMC::WriteField("springs", json, in_value.springs);
}
inline void to_json(nlohmann::json &json, Expression const &in_value) {
  VRMC::WriteField("morphTargetBinds", json, in_value.morphTargetBinds);
  VRMC::WriteField("materialColorBinds", json, in_value.materialColorBinds);
  VRMC::WriteField("textureTransformBinds", json,
                   in_value.textureTransformBinds);
  VRMC::WriteField("isBinary", json, in_value.isBinary, false);
  VRMC::WriteField("overrideBlink", json, in_value.overrideBlink,
                   Expression::ExpressionOverrideType::None);
  VRMC::WriteField("overrideLookAt", json, in_value.overrideLookAt,
                   Expression::ExpressionOverrideType::None);
  VRMC::WriteField("overrideMouth", json, in_value.overrideMouth,
                   Expression::ExpressionOverrideType::None);
}
inline void to_json(nlohmann::json &json, Expressions const &in_value) {
  VRMC::WriteField("preset", json, in_value.preset);
  VRMC::WriteField("custom", json, in_value.custom);
}
inline void to_json(nlohmann::json &json, Expressions::Preset const &in_value) {
  VRMC::WriteField("happy", json, in_value.happy);
  VRMC::WriteField("angry", json, in_value.angry);
  VRMC::WriteField("sad", json, in_value.sad);
  VRMC::WriteField("relaxed", json, in_value.relaxed);
  VRMC::WriteField("surprised", json, in_value.surprised);
  VRMC::WriteField("aa", json, in_value.aa);
  VRMC::WriteField("ih", json, in_value.ih);
  VRMC::WriteField("ou", json, in_value.ou);
  VRMC::WriteField("ee", json, in_value.ee);
  VRMC::WriteField("oh", json, in_value.oh);
  VRMC::WriteField("blink", json, in_value.blink);
  VRMC::WriteField("blinkLeft", json, in_value.blinkLeft);
  VRMC::WriteField("blinkRight", json, in_value.blinkRight);
  VRMC::WriteField("lookUp", json, in_value.lookUp);
  VRMC::WriteField("lookDown", json, in_value.lookDown);
  VRMC::WriteField("lookLeft", json, in_value.lookLeft);
  VRMC::WriteField("lookRight", json, in_value.lookRight);
  VRMC::WriteField("neutral", json, in_value.neutral);
}
inline void to_json(nlohmann::json &json, FirstPerson const &in_value) {
  VRMC::WriteField("meshAnnotations", json, in_value.meshAnnotations);
}
inline void to_json(nlohmann::json &json, Humanoid const &in_value) {
  VRMC::WriteField("humanBones", json, in_value.humanBones);
}
inline void to_json(nlohmann::json &json, LookAt const &in_value) {
  VRMC::WriteField("offsetFromHeadBone", json, in_value.offsetFromHeadBone);
  VRMC::WriteField("type", json, in_value.type, {});
  VRMC::WriteField("rangeMapHorizontalInner", json,
                   in_value.rangeMapHorizontalInner);
  VRMC::WriteField("rangeMapHorizontalOuter", json,
                   in_value.rangeMapHorizontalOuter);
  VRMC::WriteField("rangeMapVerticalDown", json, in_value.rangeMapVerticalDown);
  VRMC::WriteField("rangeMapVerticalUp", json, in_value.rangeMapVerticalUp);
}
inline void to_json(nlohmann::json &json,
                    MaterialsHdrEmissiveMultiplier const &in_value) {
  VRMC::WriteField("emissiveMultiplier", json, in_value.emissiveMultiplier,
                   1.f);
}
inline void to_json(nlohmann::json &json, MaterialsMtoon const &in_value) {
  VRMC::WriteField("specVersion", json, in_value.specVersion, {});
  VRMC::WriteField("transparentWithZWrite", json,
                   in_value.transparentWithZWrite, false);
  VRMC::WriteField("renderQueueOffsetNumber", json,
                   in_value.renderQueueOffsetNumber, static_cast<uint32_t>(0));
  VRMC::WriteField("shadeColorFactor", json, in_value.shadeColorFactor,
                   {1, 1, 1});
  VRMC::WriteField("shadeMultiplyTexture", json, in_value.shadeMultiplyTexture);
  VRMC::WriteField("shadingShiftFactor", json, in_value.shadingShiftFactor,
                   0.f);
  VRMC::WriteField("shadingShiftTexture", json, in_value.shadingShiftTexture);
  VRMC::WriteField("shadingToonyFactor", json, in_value.shadingToonyFactor,
                   0.9f);
  VRMC::WriteField("giEqualizationFactor", json, in_value.giEqualizationFactor,
                   0.9f);
  VRMC::WriteField("matcapFactor", json, in_value.matcapFactor, {1, 1, 1});
  VRMC::WriteField("matcapTexture", json, in_value.matcapTexture);
  VRMC::WriteField("parametricRimColorFactor", json,
                   in_value.parametricRimColorFactor, {0, 0, 0});
  VRMC::WriteField("rimMultiplyTexture", json, in_value.rimMultiplyTexture);
  VRMC::WriteField("rimLightingMixFactor", json, in_value.rimLightingMixFactor,
                   0.f);
  VRMC::WriteField("parametricRimFresnelPowerFactor", json,
                   in_value.parametricRimFresnelPowerFactor, 1.f);
  VRMC::WriteField("parametricRimLiftFactor", json,
                   in_value.parametricRimLiftFactor, 0.f);
  VRMC::WriteField("outlineWidthMode", json, in_value.outlineWidthMode,
                   MaterialsMtoon::OutlineWidthMode::None);
  VRMC::WriteField("outlineWidthFactor", json, in_value.outlineWidthFactor,
                   0.f);
  VRMC::WriteField("outlineWidthMultiplyTexture", json,
                   in_value.outlineWidthMultiplyTexture);
  VRMC::WriteField("outlineColorFactor", json, in_value.outlineColorFactor,
                   {0, 0, 0});
  VRMC::WriteField("outlineLightingMixFactor", json,
                   in_value.outlineLightingMixFactor, 1.f);
  VRMC::WriteField("uvAnimationMaskTexture", json,
                   in_value.uvAnimationMaskTexture);
  VRMC::WriteField("uvAnimationScrollXSpeedFactor", json,
                   in_value.uvAnimationScrollXSpeedFactor, 0.f);
  VRMC::WriteField("uvAnimationScrollYSpeedFactor", json,
                   in_value.uvAnimationScrollYSpeedFactor, 0.f);
  VRMC::WriteField("uvAnimationRotationSpeedFactor", json,
                   in_value.uvAnimationRotationSpeedFactor, 0.f);
}
inline void to_json(nlohmann::json &json,
                    NodeConstraintextension const &in_value) {
  VRMC::WriteField("specVersion", json, in_value.specVersion, {});
  VRMC::WriteField("constraint", json, in_value.constraint);
}
inline void to_json(nlohmann::json &json, Vrm const &in_value) {
  VRMC::WriteField("specVersion", json, in_value.specVersion, {});
  VRMC::WriteField("meta", json, in_value.meta);
  VRMC::WriteField("humanoid", json, in_value.humanoid);
  VRMC::WriteField("firstPerson", json, in_value.firstPerson);
  VRMC::WriteField("lookAt", json, in_value.lookAt);
  VRMC::WriteField("expressions", json, in_value.expressions);
}
inline void from_json(nlohmann::json const &json, TextureInfo &out_value) {
  VRMC::ReadRequiredField("index", json, out_value.index);
  VRMC::ReadOptionalField("texCoord", json, out_value.texCoord);
}
inline void from_json(nlohmann::json const &json,
                      ShadingShiftTextureInfo &out_value) {
  VRMC::ReadOptionalField("index", json, out_value.index);
  VRMC::ReadOptionalField("texCoord", json, out_value.texCoord);
  VRMC::ReadOptionalField("scale", json, out_value.scale);
}
inline void from_json(nlohmann::json const &json, ColliderGroup &out_value) {
  VRMC::ReadOptionalField("name", json, out_value.name);
  VRMC::ReadRequiredField("colliders", json, out_value.colliders);
}
inline void from_json(nlohmann::json const &json, SpringBoneJoint &out_value) {
  VRMC::ReadRequiredField("node", json, out_value.node);
  VRMC::ReadOptionalField("hitRadius", json, out_value.hitRadius);
  VRMC::ReadOptionalField("stiffness", json, out_value.stiffness);
  VRMC::ReadOptionalField("gravityPower", json, out_value.gravityPower);
  VRMC::ReadOptionalField("gravityDir", json, out_value.gravityDir);
  VRMC::ReadOptionalField("dragForce", json, out_value.dragForce);
}
inline void from_json(nlohmann::json const &json, ColliderShape &out_value) {
  VRMC::ReadOptionalField("sphere", json, out_value.sphere);
  VRMC::ReadOptionalField("capsule", json, out_value.capsule);
}
inline void from_json(nlohmann::json const &json,
                      ColliderShape::Sphere &out_value) {
  VRMC::ReadOptionalField("offset", json, out_value.offset);
  VRMC::ReadOptionalField("radius", json, out_value.radius);
}
inline void from_json(nlohmann::json const &json,
                      ColliderShape::Capsule &out_value) {
  VRMC::ReadOptionalField("offset", json, out_value.offset);
  VRMC::ReadOptionalField("radius", json, out_value.radius);
  VRMC::ReadOptionalField("tail", json, out_value.tail);
}
inline void from_json(nlohmann::json const &json,
                      MaterialColorBind &out_value) {
  VRMC::ReadRequiredField("material", json, out_value.material);
  VRMC::ReadRequiredField("type", json, out_value.type);
  VRMC::ReadRequiredField("targetValue", json, out_value.targetValue);
}
inline void from_json(nlohmann::json const &json, MorphTargetBind &out_value) {
  VRMC::ReadRequiredField("node", json, out_value.node);
  VRMC::ReadRequiredField("index", json, out_value.index);
  VRMC::ReadRequiredField("weight", json, out_value.weight);
}
inline void from_json(nlohmann::json const &json,
                      TextureTransformBind &out_value) {
  VRMC::ReadRequiredField("material", json, out_value.material);
  VRMC::ReadOptionalField("scale", json, out_value.scale);
  VRMC::ReadOptionalField("offset", json, out_value.offset);
}
inline void from_json(nlohmann::json const &json, MeshAnnotation &out_value) {
  VRMC::ReadRequiredField("node", json, out_value.node);
  VRMC::ReadRequiredField("type", json, out_value.type);
}
inline void from_json(nlohmann::json const &json, HumanBone &out_value) {
  VRMC::ReadRequiredField("node", json, out_value.node);
}
inline void from_json(nlohmann::json const &json, LookAtRangeMap &out_value) {
  VRMC::ReadOptionalField("inputMaxValue", json, out_value.inputMaxValue);
  VRMC::ReadOptionalField("outputScale", json, out_value.outputScale);
}
inline void from_json(nlohmann::json const &json, Meta &out_value) {
  VRMC::ReadRequiredField("name", json, out_value.name);
  VRMC::ReadOptionalField("version", json, out_value.version);
  VRMC::ReadRequiredField("authors", json, out_value.authors);
  VRMC::ReadOptionalField("copyrightInformation", json,
                          out_value.copyrightInformation);
  VRMC::ReadOptionalField("contactInformation", json,
                          out_value.contactInformation);
  VRMC::ReadOptionalField("references", json, out_value.references);
  VRMC::ReadOptionalField("thirdPartyLicenses", json,
                          out_value.thirdPartyLicenses);
  VRMC::ReadOptionalField("thumbnailImage", json, out_value.thumbnailImage);
  VRMC::ReadRequiredField("licenseUrl", json, out_value.licenseUrl);
  VRMC::ReadOptionalField("avatarPermission", json, out_value.avatarPermission);
  VRMC::ReadOptionalField("allowExcessivelyViolentUsage", json,
                          out_value.allowExcessivelyViolentUsage);
  VRMC::ReadOptionalField("allowExcessivelySexualUsage", json,
                          out_value.allowExcessivelySexualUsage);
  VRMC::ReadOptionalField("commercialUsage", json, out_value.commercialUsage);
  VRMC::ReadOptionalField("allowPoliticalOrReligiousUsage", json,
                          out_value.allowPoliticalOrReligiousUsage);
  VRMC::ReadOptionalField("allowAntisocialOrHateUsage", json,
                          out_value.allowAntisocialOrHateUsage);
  VRMC::ReadOptionalField("creditNotation", json, out_value.creditNotation);
  VRMC::ReadOptionalField("allowRedistribution", json,
                          out_value.allowRedistribution);
  VRMC::ReadOptionalField("modification", json, out_value.modification);
  VRMC::ReadOptionalField("otherLicenseUrl", json, out_value.otherLicenseUrl);
}
inline void from_json(nlohmann::json const &json, AimConstraint &out_value) {
  VRMC::ReadRequiredField("source", json, out_value.source);
  VRMC::ReadRequiredField("aimAxis", json, out_value.aimAxis);
  VRMC::ReadOptionalField("weight", json, out_value.weight);
}
inline void from_json(nlohmann::json const &json, RollConstraint &out_value) {
  VRMC::ReadRequiredField("source", json, out_value.source);
  VRMC::ReadRequiredField("rollAxis", json, out_value.rollAxis);
  VRMC::ReadOptionalField("weight", json, out_value.weight);
}
inline void from_json(nlohmann::json const &json,
                      RotationConstraint &out_value) {
  VRMC::ReadRequiredField("source", json, out_value.source);
  VRMC::ReadOptionalField("weight", json, out_value.weight);
}
inline void from_json(nlohmann::json const &json, Collider &out_value) {
  VRMC::ReadRequiredField("node", json, out_value.node);
  VRMC::ReadRequiredField("shape", json, out_value.shape);
}
inline void from_json(nlohmann::json const &json, Spring &out_value) {
  VRMC::ReadOptionalField("name", json, out_value.name);
  VRMC::ReadRequiredField("joints", json, out_value.joints);
  VRMC::ReadOptionalField("colliderGroups", json, out_value.colliderGroups);
  VRMC::ReadOptionalField("center", json, out_value.center);
}
inline void from_json(nlohmann::json const &json, HumanBones &out_value) {
  VRMC::ReadRequiredField("hips", json, out_value.hips);
  VRMC::ReadRequiredField("spine", json, out_value.spine);
  VRMC::ReadOptionalField("chest", json, out_value.chest);
  VRMC::ReadOptionalField("upperChest", json, out_value.upperChest);
  VRMC::ReadOptionalField("neck", json, out_value.neck);
  VRMC::ReadRequiredField("head", json, out_value.head);
  VRMC::ReadOptionalField("leftEye", json, out_value.leftEye);
  VRMC::ReadOptionalField("rightEye", json, out_value.rightEye);
  VRMC::ReadOptionalField("jaw", json, out_value.jaw);
  VRMC::ReadRequiredField("leftUpperLeg", json, out_value.leftUpperLeg);
  VRMC::ReadRequiredField("leftLowerLeg", json, out_value.leftLowerLeg);
  VRMC::ReadRequiredField("leftFoot", json, out_value.leftFoot);
  VRMC::ReadOptionalField("leftToes", json, out_value.leftToes);
  VRMC::ReadRequiredField("rightUpperLeg", json, out_value.rightUpperLeg);
  VRMC::ReadRequiredField("rightLowerLeg", json, out_value.rightLowerLeg);
  VRMC::ReadRequiredField("rightFoot", json, out_value.rightFoot);
  VRMC::ReadOptionalField("rightToes", json, out_value.rightToes);
  VRMC::ReadOptionalField("leftShoulder", json, out_value.leftShoulder);
  VRMC::ReadRequiredField("leftUpperArm", json, out_value.leftUpperArm);
  VRMC::ReadRequiredField("leftLowerArm", json, out_value.leftLowerArm);
  VRMC::ReadRequiredField("leftHand", json, out_value.leftHand);
  VRMC::ReadOptionalField("rightShoulder", json, out_value.rightShoulder);
  VRMC::ReadRequiredField("rightUpperArm", json, out_value.rightUpperArm);
  VRMC::ReadRequiredField("rightLowerArm", json, out_value.rightLowerArm);
  VRMC::ReadRequiredField("rightHand", json, out_value.rightHand);
  VRMC::ReadOptionalField("leftThumbProximal", json,
                          out_value.leftThumbProximal);
  VRMC::ReadOptionalField("leftThumbIntermediate", json,
                          out_value.leftThumbIntermediate);
  VRMC::ReadOptionalField("leftThumbDistal", json, out_value.leftThumbDistal);
  VRMC::ReadOptionalField("leftIndexProximal", json,
                          out_value.leftIndexProximal);
  VRMC::ReadOptionalField("leftIndexIntermediate", json,
                          out_value.leftIndexIntermediate);
  VRMC::ReadOptionalField("leftIndexDistal", json, out_value.leftIndexDistal);
  VRMC::ReadOptionalField("leftMiddleProximal", json,
                          out_value.leftMiddleProximal);
  VRMC::ReadOptionalField("leftMiddleIntermediate", json,
                          out_value.leftMiddleIntermediate);
  VRMC::ReadOptionalField("leftMiddleDistal", json, out_value.leftMiddleDistal);
  VRMC::ReadOptionalField("leftRingProximal", json, out_value.leftRingProximal);
  VRMC::ReadOptionalField("leftRingIntermediate", json,
                          out_value.leftRingIntermediate);
  VRMC::ReadOptionalField("leftRingDistal", json, out_value.leftRingDistal);
  VRMC::ReadOptionalField("leftLittleProximal", json,
                          out_value.leftLittleProximal);
  VRMC::ReadOptionalField("leftLittleIntermediate", json,
                          out_value.leftLittleIntermediate);
  VRMC::ReadOptionalField("leftLittleDistal", json, out_value.leftLittleDistal);
  VRMC::ReadOptionalField("rightThumbProximal", json,
                          out_value.rightThumbProximal);
  VRMC::ReadOptionalField("rightThumbIntermediate", json,
                          out_value.rightThumbIntermediate);
  VRMC::ReadOptionalField("rightThumbDistal", json, out_value.rightThumbDistal);
  VRMC::ReadOptionalField("rightIndexProximal", json,
                          out_value.rightIndexProximal);
  VRMC::ReadOptionalField("rightIndexIntermediate", json,
                          out_value.rightIndexIntermediate);
  VRMC::ReadOptionalField("rightIndexDistal", json, out_value.rightIndexDistal);
  VRMC::ReadOptionalField("rightMiddleProximal", json,
                          out_value.rightMiddleProximal);
  VRMC::ReadOptionalField("rightMiddleIntermediate", json,
                          out_value.rightMiddleIntermediate);
  VRMC::ReadOptionalField("rightMiddleDistal", json,
                          out_value.rightMiddleDistal);
  VRMC::ReadOptionalField("rightRingProximal", json,
                          out_value.rightRingProximal);
  VRMC::ReadOptionalField("rightRingIntermediate", json,
                          out_value.rightRingIntermediate);
  VRMC::ReadOptionalField("rightRingDistal", json, out_value.rightRingDistal);
  VRMC::ReadOptionalField("rightLittleProximal", json,
                          out_value.rightLittleProximal);
  VRMC::ReadOptionalField("rightLittleIntermediate", json,
                          out_value.rightLittleIntermediate);
  VRMC::ReadOptionalField("rightLittleDistal", json,
                          out_value.rightLittleDistal);
}
inline void from_json(nlohmann::json const &json, Constraint &out_value) {
  VRMC::ReadOptionalField("roll", json, out_value.roll);
  VRMC::ReadOptionalField("aim", json, out_value.aim);
  VRMC::ReadOptionalField("rotation", json, out_value.rotation);
}
inline void from_json(nlohmann::json const &json, SpringBone &out_value) {
  VRMC::ReadRequiredField("specVersion", json, out_value.specVersion);
  VRMC::ReadOptionalField("colliders", json, out_value.colliders);
  VRMC::ReadOptionalField("colliderGroups", json, out_value.colliderGroups);
  VRMC::ReadOptionalField("springs", json, out_value.springs);
}
inline void from_json(nlohmann::json const &json, Expression &out_value) {
  VRMC::ReadOptionalField("morphTargetBinds", json, out_value.morphTargetBinds);
  VRMC::ReadOptionalField("materialColorBinds", json,
                          out_value.materialColorBinds);
  VRMC::ReadOptionalField("textureTransformBinds", json,
                          out_value.textureTransformBinds);
  VRMC::ReadOptionalField("isBinary", json, out_value.isBinary);
  VRMC::ReadOptionalField("overrideBlink", json, out_value.overrideBlink);
  VRMC::ReadOptionalField("overrideLookAt", json, out_value.overrideLookAt);
  VRMC::ReadOptionalField("overrideMouth", json, out_value.overrideMouth);
}
inline void from_json(nlohmann::json const &json, Expressions &out_value) {
  VRMC::ReadOptionalField("preset", json, out_value.preset);
  VRMC::ReadOptionalField("custom", json, out_value.custom);
}
inline void from_json(nlohmann::json const &json,
                      Expressions::Preset &out_value) {
  VRMC::ReadOptionalField("happy", json, out_value.happy);
  VRMC::ReadOptionalField("angry", json, out_value.angry);
  VRMC::ReadOptionalField("sad", json, out_value.sad);
  VRMC::ReadOptionalField("relaxed", json, out_value.relaxed);
  VRMC::ReadOptionalField("surprised", json, out_value.surprised);
  VRMC::ReadOptionalField("aa", json, out_value.aa);
  VRMC::ReadOptionalField("ih", json, out_value.ih);
  VRMC::ReadOptionalField("ou", json, out_value.ou);
  VRMC::ReadOptionalField("ee", json, out_value.ee);
  VRMC::ReadOptionalField("oh", json, out_value.oh);
  VRMC::ReadOptionalField("blink", json, out_value.blink);
  VRMC::ReadOptionalField("blinkLeft", json, out_value.blinkLeft);
  VRMC::ReadOptionalField("blinkRight", json, out_value.blinkRight);
  VRMC::ReadOptionalField("lookUp", json, out_value.lookUp);
  VRMC::ReadOptionalField("lookDown", json, out_value.lookDown);
  VRMC::ReadOptionalField("lookLeft", json, out_value.lookLeft);
  VRMC::ReadOptionalField("lookRight", json, out_value.lookRight);
  VRMC::ReadOptionalField("neutral", json, out_value.neutral);
}
inline void from_json(nlohmann::json const &json, FirstPerson &out_value) {
  VRMC::ReadOptionalField("meshAnnotations", json, out_value.meshAnnotations);
}
inline void from_json(nlohmann::json const &json, Humanoid &out_value) {
  VRMC::ReadRequiredField("humanBones", json, out_value.humanBones);
}
inline void from_json(nlohmann::json const &json, LookAt &out_value) {
  VRMC::ReadOptionalField("offsetFromHeadBone", json,
                          out_value.offsetFromHeadBone);
  VRMC::ReadOptionalField("type", json, out_value.type);
  VRMC::ReadOptionalField("rangeMapHorizontalInner", json,
                          out_value.rangeMapHorizontalInner);
  VRMC::ReadOptionalField("rangeMapHorizontalOuter", json,
                          out_value.rangeMapHorizontalOuter);
  VRMC::ReadOptionalField("rangeMapVerticalDown", json,
                          out_value.rangeMapVerticalDown);
  VRMC::ReadOptionalField("rangeMapVerticalUp", json,
                          out_value.rangeMapVerticalUp);
}
inline void from_json(nlohmann::json const &json,
                      MaterialsHdrEmissiveMultiplier &out_value) {
  VRMC::ReadRequiredField("emissiveMultiplier", json,
                          out_value.emissiveMultiplier);
}
inline void from_json(nlohmann::json const &json, MaterialsMtoon &out_value) {
  VRMC::ReadRequiredField("specVersion", json, out_value.specVersion);
  VRMC::ReadOptionalField("transparentWithZWrite", json,
                          out_value.transparentWithZWrite);
  VRMC::ReadOptionalField("renderQueueOffsetNumber", json,
                          out_value.renderQueueOffsetNumber);
  VRMC::ReadOptionalField("shadeColorFactor", json, out_value.shadeColorFactor);
  VRMC::ReadOptionalField("shadeMultiplyTexture", json,
                          out_value.shadeMultiplyTexture);
  VRMC::ReadOptionalField("shadingShiftFactor", json,
                          out_value.shadingShiftFactor);
  VRMC::ReadOptionalField("shadingShiftTexture", json,
                          out_value.shadingShiftTexture);
  VRMC::ReadOptionalField("shadingToonyFactor", json,
                          out_value.shadingToonyFactor);
  VRMC::ReadOptionalField("giEqualizationFactor", json,
                          out_value.giEqualizationFactor);
  VRMC::ReadOptionalField("matcapFactor", json, out_value.matcapFactor);
  VRMC::ReadOptionalField("matcapTexture", json, out_value.matcapTexture);
  VRMC::ReadOptionalField("parametricRimColorFactor", json,
                          out_value.parametricRimColorFactor);
  VRMC::ReadOptionalField("rimMultiplyTexture", json,
                          out_value.rimMultiplyTexture);
  VRMC::ReadOptionalField("rimLightingMixFactor", json,
                          out_value.rimLightingMixFactor);
  VRMC::ReadOptionalField("parametricRimFresnelPowerFactor", json,
                          out_value.parametricRimFresnelPowerFactor);
  VRMC::ReadOptionalField("parametricRimLiftFactor", json,
                          out_value.parametricRimLiftFactor);
  VRMC::ReadOptionalField("outlineWidthMode", json, out_value.outlineWidthMode);
  VRMC::ReadOptionalField("outlineWidthFactor", json,
                          out_value.outlineWidthFactor);
  VRMC::ReadOptionalField("outlineWidthMultiplyTexture", json,
                          out_value.outlineWidthMultiplyTexture);
  VRMC::ReadOptionalField("outlineColorFactor", json,
                          out_value.outlineColorFactor);
  VRMC::ReadOptionalField("outlineLightingMixFactor", json,
                          out_value.outlineLightingMixFactor);
  VRMC::ReadOptionalField("uvAnimationMaskTexture", json,
                          out_value.uvAnimationMaskTexture);
  VRMC::ReadOptionalField("uvAnimationScrollXSpeedFactor", json,
                          out_value.uvAnimationScrollXSpeedFactor);
  VRMC::ReadOptionalField("uvAnimationScrollYSpeedFactor", json,
                          out_value.uvAnimationScrollYSpeedFactor);
  VRMC::ReadOptionalField("uvAnimationRotationSpeedFactor", json,
                          out_value.uvAnimationRotationSpeedFactor);
}
inline void from_json(nlohmann::json const &json,
                      NodeConstraintextension &out_value) {
  VRMC::ReadRequiredField("specVersion", json, out_value.specVersion);
  VRMC::ReadRequiredField("constraint", json, out_value.constraint);
}
inline void from_json(nlohmann::json const &json, Vrm &out_value) {
  VRMC::ReadRequiredField("specVersion", json, out_value.specVersion);
  VRMC::ReadRequiredField("meta", json, out_value.meta);
  VRMC::ReadRequiredField("humanoid", json, out_value.humanoid);
  VRMC::ReadOptionalField("firstPerson", json, out_value.firstPerson);
  VRMC::ReadOptionalField("lookAt", json, out_value.lookAt);
  VRMC::ReadOptionalField("expressions", json, out_value.expressions);
}
} // namespace VRMC_VRM_1_0
#endif

/* VRM.h is distributed under MIT license:
 *
 * Copyright (c) 2021 Kota Iguchi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
