/**
 * VRM.h - C++ header-only library for simple serialization/deserialization of
 * VRM 1.0
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
struct SecondaryanimationSpring {
  std::string comment;
  float stiffiness;
  float gravityPower;
  float gravityDir[3];
  float dragForce;
  uint32_t center;
  float hitRadius;
  std::vector<uint32_t> bones;
  std::vector<uint32_t> colliderGroups;
  nlohmann::json extensionsAndExtras{};
};

struct SecondaryanimationCollidergroup {
  uint32_t node;
  struct Collider {
    float offset[3];
    float radius;
    nlohmann::json extensionsAndExtras{};
  };

  std::vector<Collider> colliders;
  nlohmann::json extensionsAndExtras{};
};

struct Secondaryanimation {
  std::vector<SecondaryanimationSpring> boneGroups;
  std::vector<SecondaryanimationCollidergroup> colliderGroups;
  nlohmann::json extensionsAndExtras{};
};

struct BlendshapeBind {
  uint32_t mesh;
  uint32_t index;
  float weight;
  nlohmann::json extensionsAndExtras{};
};

struct BlendshapeMaterialbind {
  std::string materialName;
  std::string propertyName;
  std::vector<float> targetValue;
  nlohmann::json extensionsAndExtras{};
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
  std::vector<BlendshapeBind> binds;
  std::vector<BlendshapeMaterialbind> materialValues;
  bool isBinary;
  nlohmann::json extensionsAndExtras{};
};

struct Blendshape {
  std::vector<BlendshapeGroup> blendShapeGroups;
  nlohmann::json extensionsAndExtras{};
};

struct FirstpersonDegreemap {
  std::vector<float> curve;
  float xRange;
  float yRange;
  nlohmann::json extensionsAndExtras{};
};

struct FirstpersonMeshannotation {
  uint32_t mesh;
  std::string firstPersonFlag;
  nlohmann::json extensionsAndExtras{};
};

struct Firstperson {
  uint32_t firstPersonBone;
  float firstPersonBoneOffset[3];
  std::vector<FirstpersonMeshannotation> meshAnnotations;
  enum class LookAtTypeName : uint8_t { Bone, BlendShape };
  FirstpersonDegreemap lookAtHorizontalInner;
  FirstpersonDegreemap lookAtHorizontalOuter;
  FirstpersonDegreemap lookAtVerticalDown;
  FirstpersonDegreemap lookAtVerticalUp;
  nlohmann::json extensionsAndExtras{};
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
  uint32_t node;
  bool useDefaultValues;
  float min[3];
  float max[3];
  float center[3];
  float axisLength;
  nlohmann::json extensionsAndExtras{};
};

struct Humanoid {
  std::vector<HumanoidBone> humanBones;
  float armStretch;
  float legStretch;
  float upperArmTwist;
  float lowerArmTwist;
  float upperLegTwist;
  float lowerLegTwist;
  float feetSpacing;
  bool hasTranslationDoF;
  nlohmann::json extensionsAndExtras{};
};

struct Material {
  std::string name;
  std::string shader;
  uint32_t renderQueue;
  std::unordered_map<std::string, float> floatProperties;
  std::unordered_map<std::string, float[4]> vectorProperties;
  std::unordered_map<std::string, uint32_t> textureProperties;
  std::unordered_map<std::string, bool> keywordMap;
  std::unordered_map<std::string, std::string> tagMap;
  nlohmann::json extensionsAndExtras{};
};

struct Meta {
  std::string title;
  std::string version;
  std::string author;
  std::string contactInformation;
  std::string reference;
  uint32_t texture;
  enum class AllowedUserName : uint8_t {
    OnlyAuthor,
    ExplicitlyLicensedPerson,
    Everyone
  };
  enum class ViolentUssageName : uint8_t { Disallow, Allow };
  enum class SexualUssageName : uint8_t { Disallow, Allow };
  enum class CommercialUssageName : uint8_t { Disallow, Allow };
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
  std::string otherLicenseUrl;
  nlohmann::json extensionsAndExtras{};
};

struct Vrm {
  std::string exporterVersion;
  std::string specVersion;
  Meta meta;
  Humanoid humanoid;
  Firstperson firstPerson;
  Blendshape blendShapeMaster;
  Secondaryanimation secondaryAnimation;
  std::vector<Material> materialProperties;
  nlohmann::json extensionsAndExtras{};
};
} // namespace VRM_0_0
#endif

#ifdef USE_VRM_1_0

namespace VRM_1_0 {
struct TextureInfo {
  uint32_t index;
  uint32_t texCoord;
  nlohmann::json extensionsAndExtras{};
};

struct ShadingShiftTextureInfo {
  uint32_t index;
  uint32_t texCoord;
  float scale = 1.f;
  nlohmann::json extensionsAndExtras{};
};

enum class ObjectSpace : uint8_t { Model, Local };
struct ColliderGroup {
  std::string name;
  std::vector<uint32_t> colliders;
  nlohmann::json extensionsAndExtras{};
};

struct SpringBoneJoint {
  uint32_t node;
  float hitRadius;
  float stiffness = 1.f;
  float gravityPower;
  std::vector<float> gravityDir;
  float dragForce = 0.5f;
  nlohmann::json extensionsAndExtras{};
};

struct ColliderShape {
  struct Sphere {
    std::vector<float> offset;
    float radius;
    nlohmann::json extensionsAndExtras{};
  };

  Sphere sphere;
  struct Capsule {
    std::vector<float> offset;
    float radius;
    std::vector<float> tail;
    nlohmann::json extensionsAndExtras{};
  };

  Capsule capsule;
  nlohmann::json extensionsAndExtras{};
};

struct MaterialColorBind {
  uint32_t material;
  enum class MaterialColorType : uint8_t {
    Color,
    EmissionColor,
    ShadeColor,
    RimColor,
    OutlineColor
  };
  std::vector<float> targetValue;
  nlohmann::json extensionsAndExtras{};
};

struct MorphTargetBind {
  uint32_t node;
  uint32_t index;
  float weight;
  nlohmann::json extensionsAndExtras{};
};

struct TextureTransformBind {
  uint32_t material;
  std::vector<float> scale;
  std::vector<float> offset;
  nlohmann::json extensionsAndExtras{};
};

struct MeshAnnotation {
  uint32_t node;
  enum class FirstPersonType : uint8_t {
    Auto,
    Both,
    ThirdPersonOnly,
    FirstPersonOnly
  };
  nlohmann::json extensionsAndExtras{};
};

struct HumanBone {
  uint32_t node;
  nlohmann::json extensionsAndExtras{};
};

struct LookAtRangeMap {
  float inputMaxValue;
  float outputScale;
  nlohmann::json extensionsAndExtras{};
};

struct Meta {
  std::string name;
  std::string version;
  std::vector<std::string> authors;
  std::string copyrightInformation;
  std::string contactInformation;
  std::vector<std::string> references;
  std::string thirdPartyLicenses;
  uint32_t thumbnailImage;
  std::string licenseUrl;
  enum class AvatarPermissionType : uint8_t {
    OnlyAuthor,
    OnlySeparatelyLicensedPerson,
    Everyone
  };
  bool allowExcessivelyViolentUsage;
  bool allowExcessivelySexualUsage;
  enum class CommercialUsageType : uint8_t {
    PersonalNonProfit,
    PersonalProfit,
    Corporation
  };
  bool allowPoliticalOrReligiousUsage;
  bool allowAntisocialOrHateUsage;
  enum class CreditNotationType : uint8_t { Required, Unnecessary };
  bool allowRedistribution;
  enum class ModificationType : uint8_t {
    Prohibited,
    AllowModification,
    AllowModificationRedistribution
  };
  std::string otherLicenseUrl;
  nlohmann::json extensionsAndExtras{};
};

struct AimConstraint {
  uint32_t source;
  ObjectSpace sourceSpace;
  ObjectSpace destinationSpace;
  std::vector<float> aimVector;
  std::vector<float> upVector;
  std::vector<bool> freezeAxes;
  float weight = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct PositionConstraint {
  uint32_t source;
  ObjectSpace sourceSpace;
  ObjectSpace destinationSpace;
  std::vector<bool> freezeAxes;
  float weight = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct RotationConstraint {
  uint32_t source;
  ObjectSpace sourceSpace;
  ObjectSpace destinationSpace;
  std::vector<bool> freezeAxes;
  float weight = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct Collider {
  uint32_t node;
  ColliderShape shape;
  nlohmann::json extensionsAndExtras{};
};

struct Spring {
  std::string name;
  std::vector<SpringBoneJoint> joints;
  std::vector<uint32_t> colliderGroups;
  nlohmann::json extensionsAndExtras{};
};

struct HumanBones {
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

struct Constraint {
  PositionConstraint position;
  RotationConstraint rotation;
  AimConstraint aim;
  nlohmann::json extensionsAndExtras{};
};

struct SpringBone {
  std::string specVersion;
  std::vector<Collider> colliders;
  std::vector<ColliderGroup> colliderGroups;
  std::vector<Spring> springs;
  nlohmann::json extensionsAndExtras{};
};

struct Expression {
  std::vector<MorphTargetBind> morphTargetBinds;
  std::vector<MaterialColorBind> materialColorBinds;
  std::vector<TextureTransformBind> textureTransformBinds;
  bool isBinary;
  enum class ExpressionOverrideType : uint8_t { None, Block, Blend };
  nlohmann::json extensionsAndExtras{};
};

struct Expressions {
  struct Preset {
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

struct FirstPerson {
  std::vector<MeshAnnotation> meshAnnotations;
  nlohmann::json extensionsAndExtras{};
};

struct Humanoid {
  HumanBones humanBones;
  nlohmann::json extensionsAndExtras{};
};

struct LookAt {
  std::vector<float> offsetFromHeadBone;
  enum class LookAtType : uint8_t { Bone, Expression };
  LookAtRangeMap rangeMapHorizontalInner;
  LookAtRangeMap rangeMapHorizontalOuter;
  LookAtRangeMap rangeMapVerticalDown;
  LookAtRangeMap rangeMapVerticalUp;
  nlohmann::json extensionsAndExtras{};
};

struct MaterialsHdrEmissiveMultiplier {
  float emissiveMultiplier = 1.f;
  nlohmann::json extensionsAndExtras{};
};

struct MaterialsMtoon {
  std::string specVersion;
  bool transparentWithZWrite = false;
  uint32_t renderQueueOffsetNumber;
  std::vector<float> shadeColorFactor;
  TextureInfo shadeMultiplyTexture;
  float shadingShiftFactor;
  ShadingShiftTextureInfo shadingShiftTexture;
  float shadingToonyFactor = 0.9f;
  float giEqualizationFactor = 0.9f;
  std::vector<float> matcapFactor;
  TextureInfo matcapTexture;
  std::vector<float> parametricRimColorFactor;
  TextureInfo rimMultiplyTexture;
  float rimLightingMixFactor;
  float parametricRimFresnelPowerFactor = 1.f;
  float parametricRimLiftFactor;
  enum class OutlineWidthMode : uint8_t {
    None,
    WorldCoordinates,
    ScreenCoordinates
  };
  float outlineWidthFactor;
  TextureInfo outlineWidthMultiplyTexture;
  std::vector<float> outlineColorFactor;
  float outlineLightingMixFactor = 1.f;
  TextureInfo uvAnimationMaskTexture;
  float uvAnimationScrollXSpeedFactor;
  float uvAnimationScrollYSpeedFactor;
  float uvAnimationRotationSpeedFactor;
  nlohmann::json extensionsAndExtras{};
};

struct NodeConstraintextension {
  std::string specVersion;
  Constraint constraint;
  nlohmann::json extensionsAndExtras{};
};

struct Vrm {
  std::string specVersion;
  Meta meta;
  Humanoid humanoid;
  FirstPerson firstPerson;
  LookAt lookAt;
  Expressions expressions;
  nlohmann::json extensionsAndExtras{};
};
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
