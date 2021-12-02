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

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#endif

#include <fx/gltf.h>
#include <nlohmann/json.hpp>

#ifdef USE_VRM_0_0

namespace VRM_0_0 {
struct SecondaryanimationSpring : fx::gltf::NeverEmpty {
  std::string comment;
  float stiffiness{};
  float gravityPower{};
  std::vector<float> gravityDir;
  float dragForce{};
  uint32_t center{};
  float hitRadius{};
  std::vector<uint32_t> bones{};
  std::vector<uint32_t> colliderGroups{};
  nlohmann::json extensionsAndExtras{};
};

struct SecondaryanimationCollidergroup : fx::gltf::NeverEmpty {
  uint32_t node{};
  struct Collider : fx::gltf::NeverEmpty {
    std::vector<float> offset;
    float radius{};
    nlohmann::json extensionsAndExtras{};
  };

  std::vector<Collider> colliders{};
  nlohmann::json extensionsAndExtras{};
};

struct Secondaryanimation : fx::gltf::NeverEmpty {
  std::vector<SecondaryanimationSpring> boneGroups{};
  std::vector<SecondaryanimationCollidergroup> colliderGroups{};
  nlohmann::json extensionsAndExtras{};
};

struct BlendshapeBind : fx::gltf::NeverEmpty {
  uint32_t mesh{};
  uint32_t index{};
  float weight{};
  nlohmann::json extensionsAndExtras{};
};

struct BlendshapeMaterialbind : fx::gltf::NeverEmpty {
  std::string materialName;
  std::string propertyName;
  std::vector<float> targetValue{};
  nlohmann::json extensionsAndExtras{};
};

struct BlendshapeGroup : fx::gltf::NeverEmpty {
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
  nlohmann::json extensionsAndExtras{};
};

struct Blendshape : fx::gltf::NeverEmpty {
  std::vector<BlendshapeGroup> blendShapeGroups{};
  nlohmann::json extensionsAndExtras{};
};

struct FirstpersonDegreemap : fx::gltf::NeverEmpty {
  std::vector<float> curve{};
  float xRange{};
  float yRange{};
  nlohmann::json extensionsAndExtras{};
};

struct FirstpersonMeshannotation : fx::gltf::NeverEmpty {
  uint32_t mesh{};
  std::string firstPersonFlag;
  nlohmann::json extensionsAndExtras{};
};

struct Firstperson : fx::gltf::NeverEmpty {
  uint32_t firstPersonBone{};
  std::vector<float> firstPersonBoneOffset;
  std::vector<FirstpersonMeshannotation> meshAnnotations{};
  enum class LookAtTypeName : uint8_t { Bone, BlendShape };
  LookAtTypeName lookAtTypeName;
  FirstpersonDegreemap lookAtHorizontalInner;
  FirstpersonDegreemap lookAtHorizontalOuter;
  FirstpersonDegreemap lookAtVerticalDown;
  FirstpersonDegreemap lookAtVerticalUp;
  nlohmann::json extensionsAndExtras{};
};

struct HumanoidBone : fx::gltf::NeverEmpty {
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
  std::vector<float> min;
  std::vector<float> max;
  std::vector<float> center;
  float axisLength{};
  nlohmann::json extensionsAndExtras{};
};

struct Humanoid : fx::gltf::NeverEmpty {
  std::vector<HumanoidBone> humanBones{};
  float armStretch{};
  float legStretch{};
  float upperArmTwist{};
  float lowerArmTwist{};
  float upperLegTwist{};
  float lowerLegTwist{};
  float feetSpacing{};
  bool hasTranslationDoF{};
  nlohmann::json extensionsAndExtras{};
};

struct Material : fx::gltf::NeverEmpty {
  std::string name;
  std::string shader;
  uint32_t renderQueue{};
  std::unordered_map<std::string, float> floatProperties{};
  std::unordered_map<std::string, std::vector<float>> vectorProperties{};
  std::unordered_map<std::string, uint32_t> textureProperties{};
  std::unordered_map<std::string, bool> keywordMap{};
  std::unordered_map<std::string, std::string> tagMap{};
  nlohmann::json extensionsAndExtras{};
};

struct Meta : fx::gltf::NeverEmpty {
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
  nlohmann::json extensionsAndExtras{};
};

struct Vrm : fx::gltf::NeverEmpty {
  std::string exporterVersion;
  std::string specVersion;
  Meta meta;
  Humanoid humanoid;
  Firstperson firstPerson;
  Blendshape blendShapeMaster;
  Secondaryanimation secondaryAnimation;
  std::vector<Material> materialProperties{};
  nlohmann::json extensionsAndExtras{};
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
    throw fx::gltf::invalid_gltf_document("Unknown PresetName value");
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
    throw fx::gltf::invalid_gltf_document("Unknown LookAtTypeName value");
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
    throw fx::gltf::invalid_gltf_document("Unknown Bone value");
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
    throw fx::gltf::invalid_gltf_document("Unknown AllowedUserName value");
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
    throw fx::gltf::invalid_gltf_document("Unknown ViolentUssageName value");
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
    throw fx::gltf::invalid_gltf_document("Unknown SexualUssageName value");
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
    throw fx::gltf::invalid_gltf_document("Unknown CommercialUssageName value");
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
    throw fx::gltf::invalid_gltf_document("Unknown LicenseName value");
  }
}
inline void to_json(nlohmann::json &json,
                    SecondaryanimationSpring const &in_value) {
  fx::gltf::detail::WriteField("comment", json, in_value.comment, {});
  fx::gltf::detail::WriteField("stiffiness", json, in_value.stiffiness, 0.f);
  fx::gltf::detail::WriteField("gravityPower", json, in_value.gravityPower,
                               0.f);
  fx::gltf::detail::WriteField("gravityDir", json, in_value.gravityDir);
  fx::gltf::detail::WriteField("dragForce", json, in_value.dragForce, 0.f);
  fx::gltf::detail::WriteField("center", json, in_value.center,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("hitRadius", json, in_value.hitRadius, 0.f);
  fx::gltf::detail::WriteField("bones", json, in_value.bones);
  fx::gltf::detail::WriteField("colliderGroups", json, in_value.colliderGroups);
}
inline void to_json(nlohmann::json &json,
                    SecondaryanimationCollidergroup const &in_value) {
  fx::gltf::detail::WriteField("node", json, in_value.node,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("colliders", json, in_value.colliders);
}
inline void to_json(nlohmann::json &json,
                    SecondaryanimationCollidergroup::Collider const &in_value) {
  fx::gltf::detail::WriteField("offset", json, in_value.offset);
  fx::gltf::detail::WriteField("radius", json, in_value.radius, 0.f);
}
inline void to_json(nlohmann::json &json, Secondaryanimation const &in_value) {
  fx::gltf::detail::WriteField("boneGroups", json, in_value.boneGroups);
  fx::gltf::detail::WriteField("colliderGroups", json, in_value.colliderGroups);
}
inline void to_json(nlohmann::json &json, BlendshapeBind const &in_value) {
  fx::gltf::detail::WriteField("mesh", json, in_value.mesh,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("index", json, in_value.index,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("weight", json, in_value.weight, 0.f);
}
inline void to_json(nlohmann::json &json,
                    BlendshapeMaterialbind const &in_value) {
  fx::gltf::detail::WriteField("materialName", json, in_value.materialName, {});
  fx::gltf::detail::WriteField("propertyName", json, in_value.propertyName, {});
  fx::gltf::detail::WriteField("targetValue", json, in_value.targetValue);
}
inline void to_json(nlohmann::json &json, BlendshapeGroup const &in_value) {
  fx::gltf::detail::WriteField("name", json, in_value.name, {});
  fx::gltf::detail::WriteField("presetName", json, in_value.presetName, {});
  fx::gltf::detail::WriteField("binds", json, in_value.binds);
  fx::gltf::detail::WriteField("materialValues", json, in_value.materialValues);
  fx::gltf::detail::WriteField("isBinary", json, in_value.isBinary, false);
}
inline void to_json(nlohmann::json &json, Blendshape const &in_value) {
  fx::gltf::detail::WriteField("blendShapeGroups", json,
                               in_value.blendShapeGroups);
}
inline void to_json(nlohmann::json &json,
                    FirstpersonDegreemap const &in_value) {
  fx::gltf::detail::WriteField("curve", json, in_value.curve);
  fx::gltf::detail::WriteField("xRange", json, in_value.xRange, 0.f);
  fx::gltf::detail::WriteField("yRange", json, in_value.yRange, 0.f);
}
inline void to_json(nlohmann::json &json,
                    FirstpersonMeshannotation const &in_value) {
  fx::gltf::detail::WriteField("mesh", json, in_value.mesh,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("firstPersonFlag", json,
                               in_value.firstPersonFlag, {});
}
inline void to_json(nlohmann::json &json, Firstperson const &in_value) {
  fx::gltf::detail::WriteField("firstPersonBone", json,
                               in_value.firstPersonBone,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("firstPersonBoneOffset", json,
                               in_value.firstPersonBoneOffset);
  fx::gltf::detail::WriteField("meshAnnotations", json,
                               in_value.meshAnnotations);
  fx::gltf::detail::WriteField("lookAtTypeName", json, in_value.lookAtTypeName,
                               {});
  fx::gltf::detail::WriteField("lookAtHorizontalInner", json,
                               in_value.lookAtHorizontalInner);
  fx::gltf::detail::WriteField("lookAtHorizontalOuter", json,
                               in_value.lookAtHorizontalOuter);
  fx::gltf::detail::WriteField("lookAtVerticalDown", json,
                               in_value.lookAtVerticalDown);
  fx::gltf::detail::WriteField("lookAtVerticalUp", json,
                               in_value.lookAtVerticalUp);
}
inline void to_json(nlohmann::json &json, HumanoidBone const &in_value) {
  fx::gltf::detail::WriteField("bone", json, in_value.bone, {});
  fx::gltf::detail::WriteField("node", json, in_value.node,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("useDefaultValues", json,
                               in_value.useDefaultValues, false);
  fx::gltf::detail::WriteField("min", json, in_value.min);
  fx::gltf::detail::WriteField("max", json, in_value.max);
  fx::gltf::detail::WriteField("center", json, in_value.center);
  fx::gltf::detail::WriteField("axisLength", json, in_value.axisLength, 0.f);
}
inline void to_json(nlohmann::json &json, Humanoid const &in_value) {
  fx::gltf::detail::WriteField("humanBones", json, in_value.humanBones);
  fx::gltf::detail::WriteField("armStretch", json, in_value.armStretch, 0.f);
  fx::gltf::detail::WriteField("legStretch", json, in_value.legStretch, 0.f);
  fx::gltf::detail::WriteField("upperArmTwist", json, in_value.upperArmTwist,
                               0.f);
  fx::gltf::detail::WriteField("lowerArmTwist", json, in_value.lowerArmTwist,
                               0.f);
  fx::gltf::detail::WriteField("upperLegTwist", json, in_value.upperLegTwist,
                               0.f);
  fx::gltf::detail::WriteField("lowerLegTwist", json, in_value.lowerLegTwist,
                               0.f);
  fx::gltf::detail::WriteField("feetSpacing", json, in_value.feetSpacing, 0.f);
  fx::gltf::detail::WriteField("hasTranslationDoF", json,
                               in_value.hasTranslationDoF, false);
}
inline void to_json(nlohmann::json &json, Material const &in_value) {
  fx::gltf::detail::WriteField("name", json, in_value.name, {});
  fx::gltf::detail::WriteField("shader", json, in_value.shader, {});
  fx::gltf::detail::WriteField("renderQueue", json, in_value.renderQueue,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("floatProperties", json,
                               in_value.floatProperties);
  fx::gltf::detail::WriteField("vectorProperties", json,
                               in_value.vectorProperties);
  fx::gltf::detail::WriteField("textureProperties", json,
                               in_value.textureProperties);
  fx::gltf::detail::WriteField("keywordMap", json, in_value.keywordMap);
  fx::gltf::detail::WriteField("tagMap", json, in_value.tagMap);
}
inline void to_json(nlohmann::json &json, Meta const &in_value) {
  fx::gltf::detail::WriteField("title", json, in_value.title, {});
  fx::gltf::detail::WriteField("version", json, in_value.version, {});
  fx::gltf::detail::WriteField("author", json, in_value.author, {});
  fx::gltf::detail::WriteField("contactInformation", json,
                               in_value.contactInformation, {});
  fx::gltf::detail::WriteField("reference", json, in_value.reference, {});
  fx::gltf::detail::WriteField("texture", json, in_value.texture,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("allowedUserName", json,
                               in_value.allowedUserName, {});
  fx::gltf::detail::WriteField("violentUssageName", json,
                               in_value.violentUssageName, {});
  fx::gltf::detail::WriteField("sexualUssageName", json,
                               in_value.sexualUssageName, {});
  fx::gltf::detail::WriteField("commercialUssageName", json,
                               in_value.commercialUssageName, {});
  fx::gltf::detail::WriteField("otherPermissionUrl", json,
                               in_value.otherPermissionUrl, {});
  fx::gltf::detail::WriteField("licenseName", json, in_value.licenseName, {});
  fx::gltf::detail::WriteField("otherLicenseUrl", json,
                               in_value.otherLicenseUrl, {});
}
inline void to_json(nlohmann::json &json, Vrm const &in_value) {
  fx::gltf::detail::WriteField("exporterVersion", json,
                               in_value.exporterVersion, {});
  fx::gltf::detail::WriteField("specVersion", json, in_value.specVersion, {});
  fx::gltf::detail::WriteField("meta", json, in_value.meta);
  fx::gltf::detail::WriteField("humanoid", json, in_value.humanoid);
  fx::gltf::detail::WriteField("firstPerson", json, in_value.firstPerson);
  fx::gltf::detail::WriteField("blendShapeMaster", json,
                               in_value.blendShapeMaster);
  fx::gltf::detail::WriteField("secondaryAnimation", json,
                               in_value.secondaryAnimation);
  fx::gltf::detail::WriteField("materialProperties", json,
                               in_value.materialProperties);
}
inline void from_json(nlohmann::json const &json,
                      SecondaryanimationSpring &out_value) {
  fx::gltf::detail::ReadOptionalField("comment", json, out_value.comment);
  fx::gltf::detail::ReadOptionalField("stiffiness", json, out_value.stiffiness);
  fx::gltf::detail::ReadOptionalField("gravityPower", json,
                                      out_value.gravityPower);
  fx::gltf::detail::ReadOptionalField("gravityDir", json, out_value.gravityDir);
  fx::gltf::detail::ReadOptionalField("dragForce", json, out_value.dragForce);
  fx::gltf::detail::ReadOptionalField("center", json, out_value.center);
  fx::gltf::detail::ReadOptionalField("hitRadius", json, out_value.hitRadius);
  fx::gltf::detail::ReadOptionalField("bones", json, out_value.bones);
  fx::gltf::detail::ReadOptionalField("colliderGroups", json,
                                      out_value.colliderGroups);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      SecondaryanimationCollidergroup &out_value) {
  fx::gltf::detail::ReadOptionalField("node", json, out_value.node);
  fx::gltf::detail::ReadOptionalField("colliders", json, out_value.colliders);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      SecondaryanimationCollidergroup::Collider &out_value) {
  fx::gltf::detail::ReadOptionalField("offset", json, out_value.offset);
  fx::gltf::detail::ReadOptionalField("radius", json, out_value.radius);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      Secondaryanimation &out_value) {
  fx::gltf::detail::ReadOptionalField("boneGroups", json, out_value.boneGroups);
  fx::gltf::detail::ReadOptionalField("colliderGroups", json,
                                      out_value.colliderGroups);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, BlendshapeBind &out_value) {
  fx::gltf::detail::ReadOptionalField("mesh", json, out_value.mesh);
  fx::gltf::detail::ReadOptionalField("index", json, out_value.index);
  fx::gltf::detail::ReadOptionalField("weight", json, out_value.weight);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      BlendshapeMaterialbind &out_value) {
  fx::gltf::detail::ReadOptionalField("materialName", json,
                                      out_value.materialName);
  fx::gltf::detail::ReadOptionalField("propertyName", json,
                                      out_value.propertyName);
  fx::gltf::detail::ReadOptionalField("targetValue", json,
                                      out_value.targetValue);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, BlendshapeGroup &out_value) {
  fx::gltf::detail::ReadOptionalField("name", json, out_value.name);
  fx::gltf::detail::ReadOptionalField("presetName", json, out_value.presetName);
  fx::gltf::detail::ReadOptionalField("binds", json, out_value.binds);
  fx::gltf::detail::ReadOptionalField("materialValues", json,
                                      out_value.materialValues);
  fx::gltf::detail::ReadOptionalField("isBinary", json, out_value.isBinary);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Blendshape &out_value) {
  fx::gltf::detail::ReadOptionalField("blendShapeGroups", json,
                                      out_value.blendShapeGroups);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      FirstpersonDegreemap &out_value) {
  fx::gltf::detail::ReadOptionalField("curve", json, out_value.curve);
  fx::gltf::detail::ReadOptionalField("xRange", json, out_value.xRange);
  fx::gltf::detail::ReadOptionalField("yRange", json, out_value.yRange);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      FirstpersonMeshannotation &out_value) {
  fx::gltf::detail::ReadOptionalField("mesh", json, out_value.mesh);
  fx::gltf::detail::ReadOptionalField("firstPersonFlag", json,
                                      out_value.firstPersonFlag);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Firstperson &out_value) {
  fx::gltf::detail::ReadOptionalField("firstPersonBone", json,
                                      out_value.firstPersonBone);
  fx::gltf::detail::ReadOptionalField("firstPersonBoneOffset", json,
                                      out_value.firstPersonBoneOffset);
  fx::gltf::detail::ReadOptionalField("meshAnnotations", json,
                                      out_value.meshAnnotations);
  fx::gltf::detail::ReadOptionalField("lookAtTypeName", json,
                                      out_value.lookAtTypeName);
  fx::gltf::detail::ReadOptionalField("lookAtHorizontalInner", json,
                                      out_value.lookAtHorizontalInner);
  fx::gltf::detail::ReadOptionalField("lookAtHorizontalOuter", json,
                                      out_value.lookAtHorizontalOuter);
  fx::gltf::detail::ReadOptionalField("lookAtVerticalDown", json,
                                      out_value.lookAtVerticalDown);
  fx::gltf::detail::ReadOptionalField("lookAtVerticalUp", json,
                                      out_value.lookAtVerticalUp);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, HumanoidBone &out_value) {
  fx::gltf::detail::ReadOptionalField("bone", json, out_value.bone);
  fx::gltf::detail::ReadOptionalField("node", json, out_value.node);
  fx::gltf::detail::ReadOptionalField("useDefaultValues", json,
                                      out_value.useDefaultValues);
  fx::gltf::detail::ReadOptionalField("min", json, out_value.min);
  fx::gltf::detail::ReadOptionalField("max", json, out_value.max);
  fx::gltf::detail::ReadOptionalField("center", json, out_value.center);
  fx::gltf::detail::ReadOptionalField("axisLength", json, out_value.axisLength);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Humanoid &out_value) {
  fx::gltf::detail::ReadOptionalField("humanBones", json, out_value.humanBones);
  fx::gltf::detail::ReadOptionalField("armStretch", json, out_value.armStretch);
  fx::gltf::detail::ReadOptionalField("legStretch", json, out_value.legStretch);
  fx::gltf::detail::ReadOptionalField("upperArmTwist", json,
                                      out_value.upperArmTwist);
  fx::gltf::detail::ReadOptionalField("lowerArmTwist", json,
                                      out_value.lowerArmTwist);
  fx::gltf::detail::ReadOptionalField("upperLegTwist", json,
                                      out_value.upperLegTwist);
  fx::gltf::detail::ReadOptionalField("lowerLegTwist", json,
                                      out_value.lowerLegTwist);
  fx::gltf::detail::ReadOptionalField("feetSpacing", json,
                                      out_value.feetSpacing);
  fx::gltf::detail::ReadOptionalField("hasTranslationDoF", json,
                                      out_value.hasTranslationDoF);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Material &out_value) {
  fx::gltf::detail::ReadOptionalField("name", json, out_value.name);
  fx::gltf::detail::ReadOptionalField("shader", json, out_value.shader);
  fx::gltf::detail::ReadOptionalField("renderQueue", json,
                                      out_value.renderQueue);
  fx::gltf::detail::ReadOptionalField("floatProperties", json,
                                      out_value.floatProperties);
  fx::gltf::detail::ReadOptionalField("vectorProperties", json,
                                      out_value.vectorProperties);
  fx::gltf::detail::ReadOptionalField("textureProperties", json,
                                      out_value.textureProperties);
  fx::gltf::detail::ReadOptionalField("keywordMap", json, out_value.keywordMap);
  fx::gltf::detail::ReadOptionalField("tagMap", json, out_value.tagMap);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Meta &out_value) {
  fx::gltf::detail::ReadOptionalField("title", json, out_value.title);
  fx::gltf::detail::ReadOptionalField("version", json, out_value.version);
  fx::gltf::detail::ReadOptionalField("author", json, out_value.author);
  fx::gltf::detail::ReadOptionalField("contactInformation", json,
                                      out_value.contactInformation);
  fx::gltf::detail::ReadOptionalField("reference", json, out_value.reference);
  fx::gltf::detail::ReadOptionalField("texture", json, out_value.texture);
  fx::gltf::detail::ReadOptionalField("allowedUserName", json,
                                      out_value.allowedUserName);
  fx::gltf::detail::ReadOptionalField("violentUssageName", json,
                                      out_value.violentUssageName);
  fx::gltf::detail::ReadOptionalField("sexualUssageName", json,
                                      out_value.sexualUssageName);
  fx::gltf::detail::ReadOptionalField("commercialUssageName", json,
                                      out_value.commercialUssageName);
  fx::gltf::detail::ReadOptionalField("otherPermissionUrl", json,
                                      out_value.otherPermissionUrl);
  fx::gltf::detail::ReadOptionalField("licenseName", json,
                                      out_value.licenseName);
  fx::gltf::detail::ReadOptionalField("otherLicenseUrl", json,
                                      out_value.otherLicenseUrl);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Vrm &out_value) {
  fx::gltf::detail::ReadOptionalField("exporterVersion", json,
                                      out_value.exporterVersion);
  fx::gltf::detail::ReadOptionalField("specVersion", json,
                                      out_value.specVersion);
  fx::gltf::detail::ReadOptionalField("meta", json, out_value.meta);
  fx::gltf::detail::ReadOptionalField("humanoid", json, out_value.humanoid);
  fx::gltf::detail::ReadOptionalField("firstPerson", json,
                                      out_value.firstPerson);
  fx::gltf::detail::ReadOptionalField("blendShapeMaster", json,
                                      out_value.blendShapeMaster);
  fx::gltf::detail::ReadOptionalField("secondaryAnimation", json,
                                      out_value.secondaryAnimation);
  fx::gltf::detail::ReadOptionalField("materialProperties", json,
                                      out_value.materialProperties);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
} // namespace VRM_0_0
#endif

#ifdef USE_VRM_1_0

namespace VRM_1_0 {
struct TextureInfo : fx::gltf::NeverEmpty {
  uint32_t index{};
  uint32_t texCoord{};
  nlohmann::json extensionsAndExtras{};
};

struct ShadingShiftTextureInfo : fx::gltf::NeverEmpty {
  uint32_t index{};
  uint32_t texCoord{};
  float scale = 1.f;
  nlohmann::json extensionsAndExtras{};
};

enum class ObjectSpace : uint8_t { Model, Local };
struct ColliderGroup : fx::gltf::NeverEmpty {
  std::string name;
  std::vector<uint32_t> colliders{};
  nlohmann::json extensionsAndExtras{};
};

struct SpringBoneJoint : fx::gltf::NeverEmpty {
  uint32_t node{};
  float hitRadius{};
  float stiffness = 1.f;
  float gravityPower{};
  std::vector<float> gravityDir = {0, -1, 0};
  float dragForce = 0.5f;
  nlohmann::json extensionsAndExtras{};
};

struct ColliderShape : fx::gltf::NeverEmpty {
  struct Sphere : fx::gltf::NeverEmpty {
    std::vector<float> offset = {0, 0, 0};
    float radius{};
    nlohmann::json extensionsAndExtras{};
  };

  Sphere sphere;
  struct Capsule : fx::gltf::NeverEmpty {
    std::vector<float> offset = {0, 0, 0};
    float radius{};
    std::vector<float> tail = {0, 0, 0};
    nlohmann::json extensionsAndExtras{};
  };

  Capsule capsule;
  nlohmann::json extensionsAndExtras{};
};

struct MaterialColorBind : fx::gltf::NeverEmpty {
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
  nlohmann::json extensionsAndExtras{};
};

struct MorphTargetBind : fx::gltf::NeverEmpty {
  uint32_t node{};
  uint32_t index{};
  float weight{};
  nlohmann::json extensionsAndExtras{};
};

struct TextureTransformBind : fx::gltf::NeverEmpty {
  uint32_t material{};
  std::vector<float> scale = {1, 1};
  std::vector<float> offset = {0, 0};
  nlohmann::json extensionsAndExtras{};
};

struct MeshAnnotation : fx::gltf::NeverEmpty {
  uint32_t node{};
  enum class FirstPersonType : uint8_t {
    Auto,
    Both,
    ThirdPersonOnly,
    FirstPersonOnly
  };
  FirstPersonType type;
  nlohmann::json extensionsAndExtras{};
};

struct HumanBone : fx::gltf::NeverEmpty {
  uint32_t node{};
  nlohmann::json extensionsAndExtras{};
};

struct LookAtRangeMap : fx::gltf::NeverEmpty {
  float inputMaxValue{};
  float outputScale{};
  nlohmann::json extensionsAndExtras{};
};

struct Meta : fx::gltf::NeverEmpty {
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
  nlohmann::json extensionsAndExtras{};
};

struct AimConstraint : fx::gltf::NeverEmpty {
  uint32_t source{};
  ObjectSpace sourceSpace;
  ObjectSpace destinationSpace;
  std::vector<float> aimVector = {0, 0, 1};
  std::vector<float> upVector = {0, 0, 1};
  std::vector<bool> freezeAxes = {true, true};
  float weight = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct PositionConstraint : fx::gltf::NeverEmpty {
  uint32_t source{};
  ObjectSpace sourceSpace;
  ObjectSpace destinationSpace;
  std::vector<bool> freezeAxes = {true, true, true};
  float weight = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct RotationConstraint : fx::gltf::NeverEmpty {
  uint32_t source{};
  ObjectSpace sourceSpace;
  ObjectSpace destinationSpace;
  std::vector<bool> freezeAxes = {true, true, true};
  float weight = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct Collider : fx::gltf::NeverEmpty {
  uint32_t node{};
  ColliderShape shape;
  nlohmann::json extensionsAndExtras{};
};

struct Spring : fx::gltf::NeverEmpty {
  std::string name;
  std::vector<SpringBoneJoint> joints{};
  std::vector<uint32_t> colliderGroups{};
  nlohmann::json extensionsAndExtras{};
};

struct HumanBones : fx::gltf::NeverEmpty {
  HumanBone hips;
  HumanBone spine;
  HumanBone chest;
  HumanBone upperChest;
  HumanBone neck;
  HumanBone head;
  HumanBone leftEye;
  HumanBone rightEye;
  HumanBone jaw;
  HumanBone leftUpperLeg;
  HumanBone leftLowerLeg;
  HumanBone leftFoot;
  HumanBone leftToes;
  HumanBone rightUpperLeg;
  HumanBone rightLowerLeg;
  HumanBone rightFoot;
  HumanBone rightToes;
  HumanBone leftShoulder;
  HumanBone leftUpperArm;
  HumanBone leftLowerArm;
  HumanBone leftHand;
  HumanBone rightShoulder;
  HumanBone rightUpperArm;
  HumanBone rightLowerArm;
  HumanBone rightHand;
  HumanBone leftThumbProximal;
  HumanBone leftThumbIntermediate;
  HumanBone leftThumbDistal;
  HumanBone leftIndexProximal;
  HumanBone leftIndexIntermediate;
  HumanBone leftIndexDistal;
  HumanBone leftMiddleProximal;
  HumanBone leftMiddleIntermediate;
  HumanBone leftMiddleDistal;
  HumanBone leftRingProximal;
  HumanBone leftRingIntermediate;
  HumanBone leftRingDistal;
  HumanBone leftLittleProximal;
  HumanBone leftLittleIntermediate;
  HumanBone leftLittleDistal;
  HumanBone rightThumbProximal;
  HumanBone rightThumbIntermediate;
  HumanBone rightThumbDistal;
  HumanBone rightIndexProximal;
  HumanBone rightIndexIntermediate;
  HumanBone rightIndexDistal;
  HumanBone rightMiddleProximal;
  HumanBone rightMiddleIntermediate;
  HumanBone rightMiddleDistal;
  HumanBone rightRingProximal;
  HumanBone rightRingIntermediate;
  HumanBone rightRingDistal;
  HumanBone rightLittleProximal;
  HumanBone rightLittleIntermediate;
  HumanBone rightLittleDistal;
  nlohmann::json extensionsAndExtras{};
};

struct Constraint : fx::gltf::NeverEmpty {
  PositionConstraint position;
  RotationConstraint rotation;
  AimConstraint aim;
  nlohmann::json extensionsAndExtras{};
};

struct SpringBone : fx::gltf::NeverEmpty {
  std::string specVersion;
  std::vector<Collider> colliders{};
  std::vector<ColliderGroup> colliderGroups{};
  std::vector<Spring> springs{};
  nlohmann::json extensionsAndExtras{};
};

struct Expression : fx::gltf::NeverEmpty {
  std::vector<MorphTargetBind> morphTargetBinds{};
  std::vector<MaterialColorBind> materialColorBinds{};
  std::vector<TextureTransformBind> textureTransformBinds{};
  bool isBinary{};
  enum class ExpressionOverrideType : uint8_t { None, Block, Blend };
  ExpressionOverrideType overrideBlink = ExpressionOverrideType::None;
  ExpressionOverrideType overrideLookAt = ExpressionOverrideType::None;
  ExpressionOverrideType overrideMouth = ExpressionOverrideType::None;
  nlohmann::json extensionsAndExtras{};
};

struct Expressions : fx::gltf::NeverEmpty {
  struct Preset : fx::gltf::NeverEmpty {
    Expression happy;
    Expression angry;
    Expression sad;
    Expression relaxed;
    Expression surprised;
    Expression aa;
    Expression ih;
    Expression ou;
    Expression ee;
    Expression oh;
    Expression blink;
    Expression blinkLeft;
    Expression blinkRight;
    Expression lookUp;
    Expression lookDown;
    Expression lookLeft;
    Expression lookRight;
    nlohmann::json extensionsAndExtras{};
  };

  Preset preset;
  Expression custom;
  nlohmann::json extensionsAndExtras{};
};

struct FirstPerson : fx::gltf::NeverEmpty {
  std::vector<MeshAnnotation> meshAnnotations{};
  nlohmann::json extensionsAndExtras{};
};

struct Humanoid : fx::gltf::NeverEmpty {
  HumanBones humanBones;
  nlohmann::json extensionsAndExtras{};
};

struct LookAt : fx::gltf::NeverEmpty {
  std::vector<float> offsetFromHeadBone{};
  enum class LookAtType : uint8_t { Bone, Expression };
  LookAtType type;
  LookAtRangeMap rangeMapHorizontalInner;
  LookAtRangeMap rangeMapHorizontalOuter;
  LookAtRangeMap rangeMapVerticalDown;
  LookAtRangeMap rangeMapVerticalUp;
  nlohmann::json extensionsAndExtras{};
};

struct MaterialsHdrEmissiveMultiplier : fx::gltf::NeverEmpty {
  float emissiveMultiplier = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct MaterialsMtoon : fx::gltf::NeverEmpty {
  std::string specVersion;
  bool transparentWithZWrite{};
  uint32_t renderQueueOffsetNumber{};
  std::vector<float> shadeColorFactor = {1, 1, 1};
  TextureInfo shadeMultiplyTexture;
  float shadingShiftFactor{};
  ShadingShiftTextureInfo shadingShiftTexture;
  float shadingToonyFactor = 0.9f;
  float giEqualizationFactor = 0.9f;
  std::vector<float> matcapFactor = {1, 1, 1};
  TextureInfo matcapTexture;
  std::vector<float> parametricRimColorFactor = {0, 0, 0};
  TextureInfo rimMultiplyTexture;
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
  TextureInfo outlineWidthMultiplyTexture;
  std::vector<float> outlineColorFactor = {0, 0, 0};
  float outlineLightingMixFactor = 1.f;
  TextureInfo uvAnimationMaskTexture;
  float uvAnimationScrollXSpeedFactor{};
  float uvAnimationScrollYSpeedFactor{};
  float uvAnimationRotationSpeedFactor{};
  nlohmann::json extensionsAndExtras{};
};

struct NodeConstraintextension : fx::gltf::NeverEmpty {
  std::string specVersion;
  Constraint constraint;
  nlohmann::json extensionsAndExtras{};
};

struct Vrm : fx::gltf::NeverEmpty {
  std::string specVersion;
  Meta meta;
  Humanoid humanoid;
  FirstPerson firstPerson;
  LookAt lookAt;
  Expressions expressions;
  nlohmann::json extensionsAndExtras{};
};
inline void from_json(nlohmann::json const &json, ObjectSpace &out_value) {
  std::string type = json.get<std::string>();
  if (type == "model") {
    out_value = ObjectSpace::Model;
  } else if (type == "local") {
    out_value = ObjectSpace::Local;
  }
}

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
inline void to_json(nlohmann::json &json, ObjectSpace const &in_value) {
  switch (in_value) {
  case ObjectSpace::Model:
    json = "model";
    break;
  case ObjectSpace::Local:
    json = "local";
    break;
  default:
    throw fx::gltf::invalid_gltf_document("Unknown ObjectSpace value");
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
    throw fx::gltf::invalid_gltf_document("Unknown MaterialColorType value");
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
    throw fx::gltf::invalid_gltf_document("Unknown FirstPersonType value");
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
    throw fx::gltf::invalid_gltf_document("Unknown AvatarPermissionType value");
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
    throw fx::gltf::invalid_gltf_document("Unknown CommercialUsageType value");
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
    throw fx::gltf::invalid_gltf_document("Unknown CreditNotationType value");
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
    throw fx::gltf::invalid_gltf_document("Unknown ModificationType value");
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
    throw fx::gltf::invalid_gltf_document(
        "Unknown ExpressionOverrideType value");
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
    throw fx::gltf::invalid_gltf_document("Unknown LookAtType value");
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
    throw fx::gltf::invalid_gltf_document("Unknown OutlineWidthMode value");
  }
}
inline void to_json(nlohmann::json &json, TextureInfo const &in_value) {
  fx::gltf::detail::WriteField("index", json, in_value.index,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("texCoord", json, in_value.texCoord,
                               static_cast<uint32_t>(0));
}
inline void to_json(nlohmann::json &json,
                    ShadingShiftTextureInfo const &in_value) {
  fx::gltf::detail::WriteField("index", json, in_value.index,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("texCoord", json, in_value.texCoord,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("scale", json, in_value.scale, 1.f);
}
inline void to_json(nlohmann::json &json, ColliderGroup const &in_value) {
  fx::gltf::detail::WriteField("name", json, in_value.name, {});
  fx::gltf::detail::WriteField("colliders", json, in_value.colliders);
}
inline void to_json(nlohmann::json &json, SpringBoneJoint const &in_value) {
  fx::gltf::detail::WriteField("node", json, in_value.node,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("hitRadius", json, in_value.hitRadius, 0.f);
  fx::gltf::detail::WriteField("stiffness", json, in_value.stiffness, 1.f);
  fx::gltf::detail::WriteField("gravityPower", json, in_value.gravityPower,
                               0.f);
  fx::gltf::detail::WriteField("gravityDir", json, in_value.gravityDir,
                               {0, -1, 0});
  fx::gltf::detail::WriteField("dragForce", json, in_value.dragForce, 0.5f);
}
inline void to_json(nlohmann::json &json, ColliderShape const &in_value) {
  fx::gltf::detail::WriteField("sphere", json, in_value.sphere);
  fx::gltf::detail::WriteField("capsule", json, in_value.capsule);
}
inline void to_json(nlohmann::json &json,
                    ColliderShape::Sphere const &in_value) {
  fx::gltf::detail::WriteField("offset", json, in_value.offset, {0, 0, 0});
  fx::gltf::detail::WriteField("radius", json, in_value.radius, 0.f);
}
inline void to_json(nlohmann::json &json,
                    ColliderShape::Capsule const &in_value) {
  fx::gltf::detail::WriteField("offset", json, in_value.offset, {0, 0, 0});
  fx::gltf::detail::WriteField("radius", json, in_value.radius, 0.f);
  fx::gltf::detail::WriteField("tail", json, in_value.tail, {0, 0, 0});
}
inline void to_json(nlohmann::json &json, MaterialColorBind const &in_value) {
  fx::gltf::detail::WriteField("material", json, in_value.material,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("type", json, in_value.type, {});
  fx::gltf::detail::WriteField("targetValue", json, in_value.targetValue);
}
inline void to_json(nlohmann::json &json, MorphTargetBind const &in_value) {
  fx::gltf::detail::WriteField("node", json, in_value.node,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("index", json, in_value.index,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("weight", json, in_value.weight, 0.f);
}
inline void to_json(nlohmann::json &json,
                    TextureTransformBind const &in_value) {
  fx::gltf::detail::WriteField("material", json, in_value.material,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("scale", json, in_value.scale, {1, 1});
  fx::gltf::detail::WriteField("offset", json, in_value.offset, {0, 0});
}
inline void to_json(nlohmann::json &json, MeshAnnotation const &in_value) {
  fx::gltf::detail::WriteField("node", json, in_value.node,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("type", json, in_value.type, {});
}
inline void to_json(nlohmann::json &json, HumanBone const &in_value) {
  fx::gltf::detail::WriteField("node", json, in_value.node,
                               static_cast<uint32_t>(0));
}
inline void to_json(nlohmann::json &json, LookAtRangeMap const &in_value) {
  fx::gltf::detail::WriteField("inputMaxValue", json, in_value.inputMaxValue,
                               0.f);
  fx::gltf::detail::WriteField("outputScale", json, in_value.outputScale, 0.f);
}
inline void to_json(nlohmann::json &json, Meta const &in_value) {
  fx::gltf::detail::WriteField("name", json, in_value.name, {});
  fx::gltf::detail::WriteField("version", json, in_value.version, {});
  fx::gltf::detail::WriteField("authors", json, in_value.authors);
  fx::gltf::detail::WriteField("copyrightInformation", json,
                               in_value.copyrightInformation, {});
  fx::gltf::detail::WriteField("contactInformation", json,
                               in_value.contactInformation, {});
  fx::gltf::detail::WriteField("references", json, in_value.references);
  fx::gltf::detail::WriteField("thirdPartyLicenses", json,
                               in_value.thirdPartyLicenses, {});
  fx::gltf::detail::WriteField("thumbnailImage", json, in_value.thumbnailImage,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("licenseUrl", json, in_value.licenseUrl, {});
  fx::gltf::detail::WriteField("avatarPermission", json,
                               in_value.avatarPermission,
                               Meta::AvatarPermissionType::OnlyAuthor);
  fx::gltf::detail::WriteField("allowExcessivelyViolentUsage", json,
                               in_value.allowExcessivelyViolentUsage, false);
  fx::gltf::detail::WriteField("allowExcessivelySexualUsage", json,
                               in_value.allowExcessivelySexualUsage, false);
  fx::gltf::detail::WriteField("commercialUsage", json,
                               in_value.commercialUsage,
                               Meta::CommercialUsageType::PersonalNonProfit);
  fx::gltf::detail::WriteField("allowPoliticalOrReligiousUsage", json,
                               in_value.allowPoliticalOrReligiousUsage, false);
  fx::gltf::detail::WriteField("allowAntisocialOrHateUsage", json,
                               in_value.allowAntisocialOrHateUsage, false);
  fx::gltf::detail::WriteField("creditNotation", json, in_value.creditNotation,
                               Meta::CreditNotationType::Required);
  fx::gltf::detail::WriteField("allowRedistribution", json,
                               in_value.allowRedistribution, false);
  fx::gltf::detail::WriteField("modification", json, in_value.modification,
                               Meta::ModificationType::Prohibited);
  fx::gltf::detail::WriteField("otherLicenseUrl", json,
                               in_value.otherLicenseUrl, {});
}
inline void to_json(nlohmann::json &json, AimConstraint const &in_value) {
  fx::gltf::detail::WriteField("source", json, in_value.source,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("sourceSpace", json, in_value.sourceSpace, {});
  fx::gltf::detail::WriteField("destinationSpace", json,
                               in_value.destinationSpace, {});
  fx::gltf::detail::WriteField("aimVector", json, in_value.aimVector,
                               {0, 0, 1});
  fx::gltf::detail::WriteField("upVector", json, in_value.upVector, {0, 0, 1});
  fx::gltf::detail::WriteField("freezeAxes", json, in_value.freezeAxes,
                               {true, true});
  fx::gltf::detail::WriteField("weight", json, in_value.weight, 1.f);
}
inline void to_json(nlohmann::json &json, PositionConstraint const &in_value) {
  fx::gltf::detail::WriteField("source", json, in_value.source,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("sourceSpace", json, in_value.sourceSpace, {});
  fx::gltf::detail::WriteField("destinationSpace", json,
                               in_value.destinationSpace, {});
  fx::gltf::detail::WriteField("freezeAxes", json, in_value.freezeAxes,
                               {true, true, true});
  fx::gltf::detail::WriteField("weight", json, in_value.weight, 1.f);
}
inline void to_json(nlohmann::json &json, RotationConstraint const &in_value) {
  fx::gltf::detail::WriteField("source", json, in_value.source,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("sourceSpace", json, in_value.sourceSpace, {});
  fx::gltf::detail::WriteField("destinationSpace", json,
                               in_value.destinationSpace, {});
  fx::gltf::detail::WriteField("freezeAxes", json, in_value.freezeAxes,
                               {true, true, true});
  fx::gltf::detail::WriteField("weight", json, in_value.weight, 1.f);
}
inline void to_json(nlohmann::json &json, Collider const &in_value) {
  fx::gltf::detail::WriteField("node", json, in_value.node,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("shape", json, in_value.shape);
}
inline void to_json(nlohmann::json &json, Spring const &in_value) {
  fx::gltf::detail::WriteField("name", json, in_value.name, {});
  fx::gltf::detail::WriteField("joints", json, in_value.joints);
  fx::gltf::detail::WriteField("colliderGroups", json, in_value.colliderGroups);
}
inline void to_json(nlohmann::json &json, HumanBones const &in_value) {
  fx::gltf::detail::WriteField("hips", json, in_value.hips);
  fx::gltf::detail::WriteField("spine", json, in_value.spine);
  fx::gltf::detail::WriteField("chest", json, in_value.chest);
  fx::gltf::detail::WriteField("upperChest", json, in_value.upperChest);
  fx::gltf::detail::WriteField("neck", json, in_value.neck);
  fx::gltf::detail::WriteField("head", json, in_value.head);
  fx::gltf::detail::WriteField("leftEye", json, in_value.leftEye);
  fx::gltf::detail::WriteField("rightEye", json, in_value.rightEye);
  fx::gltf::detail::WriteField("jaw", json, in_value.jaw);
  fx::gltf::detail::WriteField("leftUpperLeg", json, in_value.leftUpperLeg);
  fx::gltf::detail::WriteField("leftLowerLeg", json, in_value.leftLowerLeg);
  fx::gltf::detail::WriteField("leftFoot", json, in_value.leftFoot);
  fx::gltf::detail::WriteField("leftToes", json, in_value.leftToes);
  fx::gltf::detail::WriteField("rightUpperLeg", json, in_value.rightUpperLeg);
  fx::gltf::detail::WriteField("rightLowerLeg", json, in_value.rightLowerLeg);
  fx::gltf::detail::WriteField("rightFoot", json, in_value.rightFoot);
  fx::gltf::detail::WriteField("rightToes", json, in_value.rightToes);
  fx::gltf::detail::WriteField("leftShoulder", json, in_value.leftShoulder);
  fx::gltf::detail::WriteField("leftUpperArm", json, in_value.leftUpperArm);
  fx::gltf::detail::WriteField("leftLowerArm", json, in_value.leftLowerArm);
  fx::gltf::detail::WriteField("leftHand", json, in_value.leftHand);
  fx::gltf::detail::WriteField("rightShoulder", json, in_value.rightShoulder);
  fx::gltf::detail::WriteField("rightUpperArm", json, in_value.rightUpperArm);
  fx::gltf::detail::WriteField("rightLowerArm", json, in_value.rightLowerArm);
  fx::gltf::detail::WriteField("rightHand", json, in_value.rightHand);
  fx::gltf::detail::WriteField("leftThumbProximal", json,
                               in_value.leftThumbProximal);
  fx::gltf::detail::WriteField("leftThumbIntermediate", json,
                               in_value.leftThumbIntermediate);
  fx::gltf::detail::WriteField("leftThumbDistal", json,
                               in_value.leftThumbDistal);
  fx::gltf::detail::WriteField("leftIndexProximal", json,
                               in_value.leftIndexProximal);
  fx::gltf::detail::WriteField("leftIndexIntermediate", json,
                               in_value.leftIndexIntermediate);
  fx::gltf::detail::WriteField("leftIndexDistal", json,
                               in_value.leftIndexDistal);
  fx::gltf::detail::WriteField("leftMiddleProximal", json,
                               in_value.leftMiddleProximal);
  fx::gltf::detail::WriteField("leftMiddleIntermediate", json,
                               in_value.leftMiddleIntermediate);
  fx::gltf::detail::WriteField("leftMiddleDistal", json,
                               in_value.leftMiddleDistal);
  fx::gltf::detail::WriteField("leftRingProximal", json,
                               in_value.leftRingProximal);
  fx::gltf::detail::WriteField("leftRingIntermediate", json,
                               in_value.leftRingIntermediate);
  fx::gltf::detail::WriteField("leftRingDistal", json, in_value.leftRingDistal);
  fx::gltf::detail::WriteField("leftLittleProximal", json,
                               in_value.leftLittleProximal);
  fx::gltf::detail::WriteField("leftLittleIntermediate", json,
                               in_value.leftLittleIntermediate);
  fx::gltf::detail::WriteField("leftLittleDistal", json,
                               in_value.leftLittleDistal);
  fx::gltf::detail::WriteField("rightThumbProximal", json,
                               in_value.rightThumbProximal);
  fx::gltf::detail::WriteField("rightThumbIntermediate", json,
                               in_value.rightThumbIntermediate);
  fx::gltf::detail::WriteField("rightThumbDistal", json,
                               in_value.rightThumbDistal);
  fx::gltf::detail::WriteField("rightIndexProximal", json,
                               in_value.rightIndexProximal);
  fx::gltf::detail::WriteField("rightIndexIntermediate", json,
                               in_value.rightIndexIntermediate);
  fx::gltf::detail::WriteField("rightIndexDistal", json,
                               in_value.rightIndexDistal);
  fx::gltf::detail::WriteField("rightMiddleProximal", json,
                               in_value.rightMiddleProximal);
  fx::gltf::detail::WriteField("rightMiddleIntermediate", json,
                               in_value.rightMiddleIntermediate);
  fx::gltf::detail::WriteField("rightMiddleDistal", json,
                               in_value.rightMiddleDistal);
  fx::gltf::detail::WriteField("rightRingProximal", json,
                               in_value.rightRingProximal);
  fx::gltf::detail::WriteField("rightRingIntermediate", json,
                               in_value.rightRingIntermediate);
  fx::gltf::detail::WriteField("rightRingDistal", json,
                               in_value.rightRingDistal);
  fx::gltf::detail::WriteField("rightLittleProximal", json,
                               in_value.rightLittleProximal);
  fx::gltf::detail::WriteField("rightLittleIntermediate", json,
                               in_value.rightLittleIntermediate);
  fx::gltf::detail::WriteField("rightLittleDistal", json,
                               in_value.rightLittleDistal);
}
inline void to_json(nlohmann::json &json, Constraint const &in_value) {
  fx::gltf::detail::WriteField("position", json, in_value.position);
  fx::gltf::detail::WriteField("rotation", json, in_value.rotation);
  fx::gltf::detail::WriteField("aim", json, in_value.aim);
}
inline void to_json(nlohmann::json &json, SpringBone const &in_value) {
  fx::gltf::detail::WriteField("specVersion", json, in_value.specVersion, {});
  fx::gltf::detail::WriteField("colliders", json, in_value.colliders);
  fx::gltf::detail::WriteField("colliderGroups", json, in_value.colliderGroups);
  fx::gltf::detail::WriteField("springs", json, in_value.springs);
}
inline void to_json(nlohmann::json &json, Expression const &in_value) {
  fx::gltf::detail::WriteField("morphTargetBinds", json,
                               in_value.morphTargetBinds);
  fx::gltf::detail::WriteField("materialColorBinds", json,
                               in_value.materialColorBinds);
  fx::gltf::detail::WriteField("textureTransformBinds", json,
                               in_value.textureTransformBinds);
  fx::gltf::detail::WriteField("isBinary", json, in_value.isBinary, false);
  fx::gltf::detail::WriteField("overrideBlink", json, in_value.overrideBlink,
                               Expression::ExpressionOverrideType::None);
  fx::gltf::detail::WriteField("overrideLookAt", json, in_value.overrideLookAt,
                               Expression::ExpressionOverrideType::None);
  fx::gltf::detail::WriteField("overrideMouth", json, in_value.overrideMouth,
                               Expression::ExpressionOverrideType::None);
}
inline void to_json(nlohmann::json &json, Expressions const &in_value) {
  fx::gltf::detail::WriteField("preset", json, in_value.preset);
  fx::gltf::detail::WriteField("custom", json, in_value.custom);
}
inline void to_json(nlohmann::json &json, Expressions::Preset const &in_value) {
  fx::gltf::detail::WriteField("happy", json, in_value.happy);
  fx::gltf::detail::WriteField("angry", json, in_value.angry);
  fx::gltf::detail::WriteField("sad", json, in_value.sad);
  fx::gltf::detail::WriteField("relaxed", json, in_value.relaxed);
  fx::gltf::detail::WriteField("surprised", json, in_value.surprised);
  fx::gltf::detail::WriteField("aa", json, in_value.aa);
  fx::gltf::detail::WriteField("ih", json, in_value.ih);
  fx::gltf::detail::WriteField("ou", json, in_value.ou);
  fx::gltf::detail::WriteField("ee", json, in_value.ee);
  fx::gltf::detail::WriteField("oh", json, in_value.oh);
  fx::gltf::detail::WriteField("blink", json, in_value.blink);
  fx::gltf::detail::WriteField("blinkLeft", json, in_value.blinkLeft);
  fx::gltf::detail::WriteField("blinkRight", json, in_value.blinkRight);
  fx::gltf::detail::WriteField("lookUp", json, in_value.lookUp);
  fx::gltf::detail::WriteField("lookDown", json, in_value.lookDown);
  fx::gltf::detail::WriteField("lookLeft", json, in_value.lookLeft);
  fx::gltf::detail::WriteField("lookRight", json, in_value.lookRight);
}
inline void to_json(nlohmann::json &json, FirstPerson const &in_value) {
  fx::gltf::detail::WriteField("meshAnnotations", json,
                               in_value.meshAnnotations);
}
inline void to_json(nlohmann::json &json, Humanoid const &in_value) {
  fx::gltf::detail::WriteField("humanBones", json, in_value.humanBones);
}
inline void to_json(nlohmann::json &json, LookAt const &in_value) {
  fx::gltf::detail::WriteField("offsetFromHeadBone", json,
                               in_value.offsetFromHeadBone);
  fx::gltf::detail::WriteField("type", json, in_value.type, {});
  fx::gltf::detail::WriteField("rangeMapHorizontalInner", json,
                               in_value.rangeMapHorizontalInner);
  fx::gltf::detail::WriteField("rangeMapHorizontalOuter", json,
                               in_value.rangeMapHorizontalOuter);
  fx::gltf::detail::WriteField("rangeMapVerticalDown", json,
                               in_value.rangeMapVerticalDown);
  fx::gltf::detail::WriteField("rangeMapVerticalUp", json,
                               in_value.rangeMapVerticalUp);
}
inline void to_json(nlohmann::json &json,
                    MaterialsHdrEmissiveMultiplier const &in_value) {
  fx::gltf::detail::WriteField("emissiveMultiplier", json,
                               in_value.emissiveMultiplier, 1.f);
}
inline void to_json(nlohmann::json &json, MaterialsMtoon const &in_value) {
  fx::gltf::detail::WriteField("specVersion", json, in_value.specVersion, {});
  fx::gltf::detail::WriteField("transparentWithZWrite", json,
                               in_value.transparentWithZWrite, false);
  fx::gltf::detail::WriteField("renderQueueOffsetNumber", json,
                               in_value.renderQueueOffsetNumber,
                               static_cast<uint32_t>(0));
  fx::gltf::detail::WriteField("shadeColorFactor", json,
                               in_value.shadeColorFactor, {1, 1, 1});
  fx::gltf::detail::WriteField("shadeMultiplyTexture", json,
                               in_value.shadeMultiplyTexture);
  fx::gltf::detail::WriteField("shadingShiftFactor", json,
                               in_value.shadingShiftFactor, 0.f);
  fx::gltf::detail::WriteField("shadingShiftTexture", json,
                               in_value.shadingShiftTexture);
  fx::gltf::detail::WriteField("shadingToonyFactor", json,
                               in_value.shadingToonyFactor, 0.9f);
  fx::gltf::detail::WriteField("giEqualizationFactor", json,
                               in_value.giEqualizationFactor, 0.9f);
  fx::gltf::detail::WriteField("matcapFactor", json, in_value.matcapFactor,
                               {1, 1, 1});
  fx::gltf::detail::WriteField("matcapTexture", json, in_value.matcapTexture);
  fx::gltf::detail::WriteField("parametricRimColorFactor", json,
                               in_value.parametricRimColorFactor, {0, 0, 0});
  fx::gltf::detail::WriteField("rimMultiplyTexture", json,
                               in_value.rimMultiplyTexture);
  fx::gltf::detail::WriteField("rimLightingMixFactor", json,
                               in_value.rimLightingMixFactor, 0.f);
  fx::gltf::detail::WriteField("parametricRimFresnelPowerFactor", json,
                               in_value.parametricRimFresnelPowerFactor, 1.f);
  fx::gltf::detail::WriteField("parametricRimLiftFactor", json,
                               in_value.parametricRimLiftFactor, 0.f);
  fx::gltf::detail::WriteField("outlineWidthMode", json,
                               in_value.outlineWidthMode,
                               MaterialsMtoon::OutlineWidthMode::None);
  fx::gltf::detail::WriteField("outlineWidthFactor", json,
                               in_value.outlineWidthFactor, 0.f);
  fx::gltf::detail::WriteField("outlineWidthMultiplyTexture", json,
                               in_value.outlineWidthMultiplyTexture);
  fx::gltf::detail::WriteField("outlineColorFactor", json,
                               in_value.outlineColorFactor, {0, 0, 0});
  fx::gltf::detail::WriteField("outlineLightingMixFactor", json,
                               in_value.outlineLightingMixFactor, 1.f);
  fx::gltf::detail::WriteField("uvAnimationMaskTexture", json,
                               in_value.uvAnimationMaskTexture);
  fx::gltf::detail::WriteField("uvAnimationScrollXSpeedFactor", json,
                               in_value.uvAnimationScrollXSpeedFactor, 0.f);
  fx::gltf::detail::WriteField("uvAnimationScrollYSpeedFactor", json,
                               in_value.uvAnimationScrollYSpeedFactor, 0.f);
  fx::gltf::detail::WriteField("uvAnimationRotationSpeedFactor", json,
                               in_value.uvAnimationRotationSpeedFactor, 0.f);
}
inline void to_json(nlohmann::json &json,
                    NodeConstraintextension const &in_value) {
  fx::gltf::detail::WriteField("specVersion", json, in_value.specVersion, {});
  fx::gltf::detail::WriteField("constraint", json, in_value.constraint);
}
inline void to_json(nlohmann::json &json, Vrm const &in_value) {
  fx::gltf::detail::WriteField("specVersion", json, in_value.specVersion, {});
  fx::gltf::detail::WriteField("meta", json, in_value.meta);
  fx::gltf::detail::WriteField("humanoid", json, in_value.humanoid);
  fx::gltf::detail::WriteField("firstPerson", json, in_value.firstPerson);
  fx::gltf::detail::WriteField("lookAt", json, in_value.lookAt);
  fx::gltf::detail::WriteField("expressions", json, in_value.expressions);
}
inline void from_json(nlohmann::json const &json, TextureInfo &out_value) {
  fx::gltf::detail::ReadRequiredField("index", json, out_value.index);
  fx::gltf::detail::ReadOptionalField("texCoord", json, out_value.texCoord);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      ShadingShiftTextureInfo &out_value) {
  fx::gltf::detail::ReadOptionalField("index", json, out_value.index);
  fx::gltf::detail::ReadOptionalField("texCoord", json, out_value.texCoord);
  fx::gltf::detail::ReadOptionalField("scale", json, out_value.scale);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, ColliderGroup &out_value) {
  fx::gltf::detail::ReadOptionalField("name", json, out_value.name);
  fx::gltf::detail::ReadRequiredField("colliders", json, out_value.colliders);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, SpringBoneJoint &out_value) {
  fx::gltf::detail::ReadRequiredField("node", json, out_value.node);
  fx::gltf::detail::ReadOptionalField("hitRadius", json, out_value.hitRadius);
  fx::gltf::detail::ReadOptionalField("stiffness", json, out_value.stiffness);
  fx::gltf::detail::ReadOptionalField("gravityPower", json,
                                      out_value.gravityPower);
  fx::gltf::detail::ReadOptionalField("gravityDir", json, out_value.gravityDir);
  fx::gltf::detail::ReadOptionalField("dragForce", json, out_value.dragForce);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, ColliderShape &out_value) {
  fx::gltf::detail::ReadOptionalField("sphere", json, out_value.sphere);
  fx::gltf::detail::ReadOptionalField("capsule", json, out_value.capsule);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      ColliderShape::Sphere &out_value) {
  fx::gltf::detail::ReadOptionalField("offset", json, out_value.offset);
  fx::gltf::detail::ReadOptionalField("radius", json, out_value.radius);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      ColliderShape::Capsule &out_value) {
  fx::gltf::detail::ReadOptionalField("offset", json, out_value.offset);
  fx::gltf::detail::ReadOptionalField("radius", json, out_value.radius);
  fx::gltf::detail::ReadOptionalField("tail", json, out_value.tail);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      MaterialColorBind &out_value) {
  fx::gltf::detail::ReadRequiredField("material", json, out_value.material);
  fx::gltf::detail::ReadRequiredField("type", json, out_value.type);
  fx::gltf::detail::ReadRequiredField("targetValue", json,
                                      out_value.targetValue);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, MorphTargetBind &out_value) {
  fx::gltf::detail::ReadRequiredField("node", json, out_value.node);
  fx::gltf::detail::ReadRequiredField("index", json, out_value.index);
  fx::gltf::detail::ReadRequiredField("weight", json, out_value.weight);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      TextureTransformBind &out_value) {
  fx::gltf::detail::ReadRequiredField("material", json, out_value.material);
  fx::gltf::detail::ReadOptionalField("scale", json, out_value.scale);
  fx::gltf::detail::ReadOptionalField("offset", json, out_value.offset);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, MeshAnnotation &out_value) {
  fx::gltf::detail::ReadRequiredField("node", json, out_value.node);
  fx::gltf::detail::ReadRequiredField("type", json, out_value.type);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, HumanBone &out_value) {
  fx::gltf::detail::ReadRequiredField("node", json, out_value.node);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, LookAtRangeMap &out_value) {
  fx::gltf::detail::ReadOptionalField("inputMaxValue", json,
                                      out_value.inputMaxValue);
  fx::gltf::detail::ReadOptionalField("outputScale", json,
                                      out_value.outputScale);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Meta &out_value) {
  fx::gltf::detail::ReadRequiredField("name", json, out_value.name);
  fx::gltf::detail::ReadOptionalField("version", json, out_value.version);
  fx::gltf::detail::ReadRequiredField("authors", json, out_value.authors);
  fx::gltf::detail::ReadOptionalField("copyrightInformation", json,
                                      out_value.copyrightInformation);
  fx::gltf::detail::ReadOptionalField("contactInformation", json,
                                      out_value.contactInformation);
  fx::gltf::detail::ReadOptionalField("references", json, out_value.references);
  fx::gltf::detail::ReadOptionalField("thirdPartyLicenses", json,
                                      out_value.thirdPartyLicenses);
  fx::gltf::detail::ReadOptionalField("thumbnailImage", json,
                                      out_value.thumbnailImage);
  fx::gltf::detail::ReadRequiredField("licenseUrl", json, out_value.licenseUrl);
  fx::gltf::detail::ReadOptionalField("avatarPermission", json,
                                      out_value.avatarPermission);
  fx::gltf::detail::ReadOptionalField("allowExcessivelyViolentUsage", json,
                                      out_value.allowExcessivelyViolentUsage);
  fx::gltf::detail::ReadOptionalField("allowExcessivelySexualUsage", json,
                                      out_value.allowExcessivelySexualUsage);
  fx::gltf::detail::ReadOptionalField("commercialUsage", json,
                                      out_value.commercialUsage);
  fx::gltf::detail::ReadOptionalField("allowPoliticalOrReligiousUsage", json,
                                      out_value.allowPoliticalOrReligiousUsage);
  fx::gltf::detail::ReadOptionalField("allowAntisocialOrHateUsage", json,
                                      out_value.allowAntisocialOrHateUsage);
  fx::gltf::detail::ReadOptionalField("creditNotation", json,
                                      out_value.creditNotation);
  fx::gltf::detail::ReadOptionalField("allowRedistribution", json,
                                      out_value.allowRedistribution);
  fx::gltf::detail::ReadOptionalField("modification", json,
                                      out_value.modification);
  fx::gltf::detail::ReadOptionalField("otherLicenseUrl", json,
                                      out_value.otherLicenseUrl);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, AimConstraint &out_value) {
  fx::gltf::detail::ReadRequiredField("source", json, out_value.source);
  fx::gltf::detail::ReadOptionalField("sourceSpace", json,
                                      out_value.sourceSpace);
  fx::gltf::detail::ReadOptionalField("destinationSpace", json,
                                      out_value.destinationSpace);
  fx::gltf::detail::ReadOptionalField("aimVector", json, out_value.aimVector);
  fx::gltf::detail::ReadOptionalField("upVector", json, out_value.upVector);
  fx::gltf::detail::ReadOptionalField("freezeAxes", json, out_value.freezeAxes);
  fx::gltf::detail::ReadOptionalField("weight", json, out_value.weight);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      PositionConstraint &out_value) {
  fx::gltf::detail::ReadRequiredField("source", json, out_value.source);
  fx::gltf::detail::ReadOptionalField("sourceSpace", json,
                                      out_value.sourceSpace);
  fx::gltf::detail::ReadOptionalField("destinationSpace", json,
                                      out_value.destinationSpace);
  fx::gltf::detail::ReadOptionalField("freezeAxes", json, out_value.freezeAxes);
  fx::gltf::detail::ReadOptionalField("weight", json, out_value.weight);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      RotationConstraint &out_value) {
  fx::gltf::detail::ReadRequiredField("source", json, out_value.source);
  fx::gltf::detail::ReadOptionalField("sourceSpace", json,
                                      out_value.sourceSpace);
  fx::gltf::detail::ReadOptionalField("destinationSpace", json,
                                      out_value.destinationSpace);
  fx::gltf::detail::ReadOptionalField("freezeAxes", json, out_value.freezeAxes);
  fx::gltf::detail::ReadOptionalField("weight", json, out_value.weight);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Collider &out_value) {
  fx::gltf::detail::ReadRequiredField("node", json, out_value.node);
  fx::gltf::detail::ReadRequiredField("shape", json, out_value.shape);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Spring &out_value) {
  fx::gltf::detail::ReadOptionalField("name", json, out_value.name);
  fx::gltf::detail::ReadRequiredField("joints", json, out_value.joints);
  fx::gltf::detail::ReadOptionalField("colliderGroups", json,
                                      out_value.colliderGroups);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, HumanBones &out_value) {
  fx::gltf::detail::ReadRequiredField("hips", json, out_value.hips);
  fx::gltf::detail::ReadRequiredField("spine", json, out_value.spine);
  fx::gltf::detail::ReadOptionalField("chest", json, out_value.chest);
  fx::gltf::detail::ReadOptionalField("upperChest", json, out_value.upperChest);
  fx::gltf::detail::ReadOptionalField("neck", json, out_value.neck);
  fx::gltf::detail::ReadRequiredField("head", json, out_value.head);
  fx::gltf::detail::ReadOptionalField("leftEye", json, out_value.leftEye);
  fx::gltf::detail::ReadOptionalField("rightEye", json, out_value.rightEye);
  fx::gltf::detail::ReadOptionalField("jaw", json, out_value.jaw);
  fx::gltf::detail::ReadRequiredField("leftUpperLeg", json,
                                      out_value.leftUpperLeg);
  fx::gltf::detail::ReadRequiredField("leftLowerLeg", json,
                                      out_value.leftLowerLeg);
  fx::gltf::detail::ReadRequiredField("leftFoot", json, out_value.leftFoot);
  fx::gltf::detail::ReadOptionalField("leftToes", json, out_value.leftToes);
  fx::gltf::detail::ReadRequiredField("rightUpperLeg", json,
                                      out_value.rightUpperLeg);
  fx::gltf::detail::ReadRequiredField("rightLowerLeg", json,
                                      out_value.rightLowerLeg);
  fx::gltf::detail::ReadRequiredField("rightFoot", json, out_value.rightFoot);
  fx::gltf::detail::ReadOptionalField("rightToes", json, out_value.rightToes);
  fx::gltf::detail::ReadOptionalField("leftShoulder", json,
                                      out_value.leftShoulder);
  fx::gltf::detail::ReadRequiredField("leftUpperArm", json,
                                      out_value.leftUpperArm);
  fx::gltf::detail::ReadRequiredField("leftLowerArm", json,
                                      out_value.leftLowerArm);
  fx::gltf::detail::ReadRequiredField("leftHand", json, out_value.leftHand);
  fx::gltf::detail::ReadOptionalField("rightShoulder", json,
                                      out_value.rightShoulder);
  fx::gltf::detail::ReadRequiredField("rightUpperArm", json,
                                      out_value.rightUpperArm);
  fx::gltf::detail::ReadRequiredField("rightLowerArm", json,
                                      out_value.rightLowerArm);
  fx::gltf::detail::ReadRequiredField("rightHand", json, out_value.rightHand);
  fx::gltf::detail::ReadOptionalField("leftThumbProximal", json,
                                      out_value.leftThumbProximal);
  fx::gltf::detail::ReadOptionalField("leftThumbIntermediate", json,
                                      out_value.leftThumbIntermediate);
  fx::gltf::detail::ReadOptionalField("leftThumbDistal", json,
                                      out_value.leftThumbDistal);
  fx::gltf::detail::ReadOptionalField("leftIndexProximal", json,
                                      out_value.leftIndexProximal);
  fx::gltf::detail::ReadOptionalField("leftIndexIntermediate", json,
                                      out_value.leftIndexIntermediate);
  fx::gltf::detail::ReadOptionalField("leftIndexDistal", json,
                                      out_value.leftIndexDistal);
  fx::gltf::detail::ReadOptionalField("leftMiddleProximal", json,
                                      out_value.leftMiddleProximal);
  fx::gltf::detail::ReadOptionalField("leftMiddleIntermediate", json,
                                      out_value.leftMiddleIntermediate);
  fx::gltf::detail::ReadOptionalField("leftMiddleDistal", json,
                                      out_value.leftMiddleDistal);
  fx::gltf::detail::ReadOptionalField("leftRingProximal", json,
                                      out_value.leftRingProximal);
  fx::gltf::detail::ReadOptionalField("leftRingIntermediate", json,
                                      out_value.leftRingIntermediate);
  fx::gltf::detail::ReadOptionalField("leftRingDistal", json,
                                      out_value.leftRingDistal);
  fx::gltf::detail::ReadOptionalField("leftLittleProximal", json,
                                      out_value.leftLittleProximal);
  fx::gltf::detail::ReadOptionalField("leftLittleIntermediate", json,
                                      out_value.leftLittleIntermediate);
  fx::gltf::detail::ReadOptionalField("leftLittleDistal", json,
                                      out_value.leftLittleDistal);
  fx::gltf::detail::ReadOptionalField("rightThumbProximal", json,
                                      out_value.rightThumbProximal);
  fx::gltf::detail::ReadOptionalField("rightThumbIntermediate", json,
                                      out_value.rightThumbIntermediate);
  fx::gltf::detail::ReadOptionalField("rightThumbDistal", json,
                                      out_value.rightThumbDistal);
  fx::gltf::detail::ReadOptionalField("rightIndexProximal", json,
                                      out_value.rightIndexProximal);
  fx::gltf::detail::ReadOptionalField("rightIndexIntermediate", json,
                                      out_value.rightIndexIntermediate);
  fx::gltf::detail::ReadOptionalField("rightIndexDistal", json,
                                      out_value.rightIndexDistal);
  fx::gltf::detail::ReadOptionalField("rightMiddleProximal", json,
                                      out_value.rightMiddleProximal);
  fx::gltf::detail::ReadOptionalField("rightMiddleIntermediate", json,
                                      out_value.rightMiddleIntermediate);
  fx::gltf::detail::ReadOptionalField("rightMiddleDistal", json,
                                      out_value.rightMiddleDistal);
  fx::gltf::detail::ReadOptionalField("rightRingProximal", json,
                                      out_value.rightRingProximal);
  fx::gltf::detail::ReadOptionalField("rightRingIntermediate", json,
                                      out_value.rightRingIntermediate);
  fx::gltf::detail::ReadOptionalField("rightRingDistal", json,
                                      out_value.rightRingDistal);
  fx::gltf::detail::ReadOptionalField("rightLittleProximal", json,
                                      out_value.rightLittleProximal);
  fx::gltf::detail::ReadOptionalField("rightLittleIntermediate", json,
                                      out_value.rightLittleIntermediate);
  fx::gltf::detail::ReadOptionalField("rightLittleDistal", json,
                                      out_value.rightLittleDistal);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Constraint &out_value) {
  fx::gltf::detail::ReadOptionalField("position", json, out_value.position);
  fx::gltf::detail::ReadOptionalField("rotation", json, out_value.rotation);
  fx::gltf::detail::ReadOptionalField("aim", json, out_value.aim);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, SpringBone &out_value) {
  fx::gltf::detail::ReadOptionalField("specVersion", json,
                                      out_value.specVersion);
  fx::gltf::detail::ReadOptionalField("colliders", json, out_value.colliders);
  fx::gltf::detail::ReadOptionalField("colliderGroups", json,
                                      out_value.colliderGroups);
  fx::gltf::detail::ReadOptionalField("springs", json, out_value.springs);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Expression &out_value) {
  fx::gltf::detail::ReadOptionalField("morphTargetBinds", json,
                                      out_value.morphTargetBinds);
  fx::gltf::detail::ReadOptionalField("materialColorBinds", json,
                                      out_value.materialColorBinds);
  fx::gltf::detail::ReadOptionalField("textureTransformBinds", json,
                                      out_value.textureTransformBinds);
  fx::gltf::detail::ReadOptionalField("isBinary", json, out_value.isBinary);
  fx::gltf::detail::ReadOptionalField("overrideBlink", json,
                                      out_value.overrideBlink);
  fx::gltf::detail::ReadOptionalField("overrideLookAt", json,
                                      out_value.overrideLookAt);
  fx::gltf::detail::ReadOptionalField("overrideMouth", json,
                                      out_value.overrideMouth);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Expressions &out_value) {
  fx::gltf::detail::ReadOptionalField("preset", json, out_value.preset);
  fx::gltf::detail::ReadOptionalField("custom", json, out_value.custom);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      Expressions::Preset &out_value) {
  fx::gltf::detail::ReadOptionalField("happy", json, out_value.happy);
  fx::gltf::detail::ReadOptionalField("angry", json, out_value.angry);
  fx::gltf::detail::ReadOptionalField("sad", json, out_value.sad);
  fx::gltf::detail::ReadOptionalField("relaxed", json, out_value.relaxed);
  fx::gltf::detail::ReadOptionalField("surprised", json, out_value.surprised);
  fx::gltf::detail::ReadOptionalField("aa", json, out_value.aa);
  fx::gltf::detail::ReadOptionalField("ih", json, out_value.ih);
  fx::gltf::detail::ReadOptionalField("ou", json, out_value.ou);
  fx::gltf::detail::ReadOptionalField("ee", json, out_value.ee);
  fx::gltf::detail::ReadOptionalField("oh", json, out_value.oh);
  fx::gltf::detail::ReadOptionalField("blink", json, out_value.blink);
  fx::gltf::detail::ReadOptionalField("blinkLeft", json, out_value.blinkLeft);
  fx::gltf::detail::ReadOptionalField("blinkRight", json, out_value.blinkRight);
  fx::gltf::detail::ReadOptionalField("lookUp", json, out_value.lookUp);
  fx::gltf::detail::ReadOptionalField("lookDown", json, out_value.lookDown);
  fx::gltf::detail::ReadOptionalField("lookLeft", json, out_value.lookLeft);
  fx::gltf::detail::ReadOptionalField("lookRight", json, out_value.lookRight);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, FirstPerson &out_value) {
  fx::gltf::detail::ReadOptionalField("meshAnnotations", json,
                                      out_value.meshAnnotations);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Humanoid &out_value) {
  fx::gltf::detail::ReadRequiredField("humanBones", json, out_value.humanBones);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, LookAt &out_value) {
  fx::gltf::detail::ReadOptionalField("offsetFromHeadBone", json,
                                      out_value.offsetFromHeadBone);
  fx::gltf::detail::ReadOptionalField("type", json, out_value.type);
  fx::gltf::detail::ReadOptionalField("rangeMapHorizontalInner", json,
                                      out_value.rangeMapHorizontalInner);
  fx::gltf::detail::ReadOptionalField("rangeMapHorizontalOuter", json,
                                      out_value.rangeMapHorizontalOuter);
  fx::gltf::detail::ReadOptionalField("rangeMapVerticalDown", json,
                                      out_value.rangeMapVerticalDown);
  fx::gltf::detail::ReadOptionalField("rangeMapVerticalUp", json,
                                      out_value.rangeMapVerticalUp);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      MaterialsHdrEmissiveMultiplier &out_value) {
  fx::gltf::detail::ReadRequiredField("emissiveMultiplier", json,
                                      out_value.emissiveMultiplier);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, MaterialsMtoon &out_value) {
  fx::gltf::detail::ReadOptionalField("specVersion", json,
                                      out_value.specVersion);
  fx::gltf::detail::ReadOptionalField("transparentWithZWrite", json,
                                      out_value.transparentWithZWrite);
  fx::gltf::detail::ReadOptionalField("renderQueueOffsetNumber", json,
                                      out_value.renderQueueOffsetNumber);
  fx::gltf::detail::ReadOptionalField("shadeColorFactor", json,
                                      out_value.shadeColorFactor);
  fx::gltf::detail::ReadOptionalField("shadeMultiplyTexture", json,
                                      out_value.shadeMultiplyTexture);
  fx::gltf::detail::ReadOptionalField("shadingShiftFactor", json,
                                      out_value.shadingShiftFactor);
  fx::gltf::detail::ReadOptionalField("shadingShiftTexture", json,
                                      out_value.shadingShiftTexture);
  fx::gltf::detail::ReadOptionalField("shadingToonyFactor", json,
                                      out_value.shadingToonyFactor);
  fx::gltf::detail::ReadOptionalField("giEqualizationFactor", json,
                                      out_value.giEqualizationFactor);
  fx::gltf::detail::ReadOptionalField("matcapFactor", json,
                                      out_value.matcapFactor);
  fx::gltf::detail::ReadOptionalField("matcapTexture", json,
                                      out_value.matcapTexture);
  fx::gltf::detail::ReadOptionalField("parametricRimColorFactor", json,
                                      out_value.parametricRimColorFactor);
  fx::gltf::detail::ReadOptionalField("rimMultiplyTexture", json,
                                      out_value.rimMultiplyTexture);
  fx::gltf::detail::ReadOptionalField("rimLightingMixFactor", json,
                                      out_value.rimLightingMixFactor);
  fx::gltf::detail::ReadOptionalField(
      "parametricRimFresnelPowerFactor", json,
      out_value.parametricRimFresnelPowerFactor);
  fx::gltf::detail::ReadOptionalField("parametricRimLiftFactor", json,
                                      out_value.parametricRimLiftFactor);
  fx::gltf::detail::ReadOptionalField("outlineWidthMode", json,
                                      out_value.outlineWidthMode);
  fx::gltf::detail::ReadOptionalField("outlineWidthFactor", json,
                                      out_value.outlineWidthFactor);
  fx::gltf::detail::ReadOptionalField("outlineWidthMultiplyTexture", json,
                                      out_value.outlineWidthMultiplyTexture);
  fx::gltf::detail::ReadOptionalField("outlineColorFactor", json,
                                      out_value.outlineColorFactor);
  fx::gltf::detail::ReadOptionalField("outlineLightingMixFactor", json,
                                      out_value.outlineLightingMixFactor);
  fx::gltf::detail::ReadOptionalField("uvAnimationMaskTexture", json,
                                      out_value.uvAnimationMaskTexture);
  fx::gltf::detail::ReadOptionalField("uvAnimationScrollXSpeedFactor", json,
                                      out_value.uvAnimationScrollXSpeedFactor);
  fx::gltf::detail::ReadOptionalField("uvAnimationScrollYSpeedFactor", json,
                                      out_value.uvAnimationScrollYSpeedFactor);
  fx::gltf::detail::ReadOptionalField("uvAnimationRotationSpeedFactor", json,
                                      out_value.uvAnimationRotationSpeedFactor);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json,
                      NodeConstraintextension &out_value) {
  fx::gltf::detail::ReadOptionalField("specVersion", json,
                                      out_value.specVersion);
  fx::gltf::detail::ReadOptionalField("constraint", json, out_value.constraint);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
inline void from_json(nlohmann::json const &json, Vrm &out_value) {
  fx::gltf::detail::ReadRequiredField("specVersion", json,
                                      out_value.specVersion);
  fx::gltf::detail::ReadRequiredField("meta", json, out_value.meta);
  fx::gltf::detail::ReadRequiredField("humanoid", json, out_value.humanoid);
  fx::gltf::detail::ReadOptionalField("firstPerson", json,
                                      out_value.firstPerson);
  fx::gltf::detail::ReadOptionalField("lookAt", json, out_value.lookAt);
  fx::gltf::detail::ReadOptionalField("expressions", json,
                                      out_value.expressions);
  fx::gltf::detail::ReadExtensionsAndExtras(json,
                                            out_value.extensionsAndExtras);
}
} // namespace VRM_1_0
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
