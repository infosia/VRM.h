#include <catch2/catch.hpp>
#include <filesystem>
#include <fx/gltf.h>

#include <nlohmann/json.hpp>

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

#define USE_VRMC_VRM_0_0
#define USE_VRMC_VRM_1_0
#include <VRMC/VRM.h>

TEST_CASE("VRM 0.x (fx-gltf)") {
  std::filesystem::path f{"../data/0.x/001.vrm"};
  const auto doc = fx::gltf::LoadFromBinary(f);

  SECTION("load-001-extensions") {
    REQUIRE(doc.extensionsUsed.size() > 0);
    REQUIRE(doc.extensionsAndExtras.size() > 0);
    REQUIRE(doc.extensionsAndExtras.contains("extensions"));

    const auto extensions = doc.extensionsAndExtras["extensions"];
    REQUIRE(extensions.contains("VRM"));
    REQUIRE(extensions["VRM"].size() > 0);

    VRMC_VRM_0_0::Vrm vrm;
    VRMC_VRM_0_0::from_json(extensions["VRM"], vrm);

    REQUIRE_FALSE(vrm.specVersion.empty());
  }

  SECTION("load-001.meta") {
    const auto extensions = doc.extensionsAndExtras["extensions"];

    VRMC_VRM_0_0::Vrm vrm;
    VRMC_VRM_0_0::from_json(extensions["VRM"], vrm);

    REQUIRE_FALSE(vrm.meta.version.empty());
    REQUIRE(vrm.meta.allowedUserName ==
            VRMC_VRM_0_0::Meta::AllowedUserName::OnlyAuthor);
  }
}

TEST_CASE("VRM 1.0 (fx-gltf)") {
  std::filesystem::path f{"../data/1.0/001.vrm"};
  const auto doc = fx::gltf::LoadFromBinary(f);

  SECTION("load-001-extensions") {
    REQUIRE(doc.extensionsUsed.size() > 0);
    REQUIRE(doc.extensionsAndExtras.size() > 0);
    REQUIRE(doc.extensionsAndExtras.contains("extensions"));

    const auto extensions = doc.extensionsAndExtras["extensions"];
    REQUIRE(extensions.contains("VRMC_vrm"));
    REQUIRE(extensions["VRMC_vrm"].size() > 0);

    VRMC_VRM_1_0::Vrm vrm;
    VRMC_VRM_1_0::from_json(extensions["VRMC_vrm"], vrm);

    REQUIRE_FALSE(vrm.specVersion.empty());
  }

  SECTION("load-001.meta") {
    const auto extensions = doc.extensionsAndExtras["extensions"];

    VRMC_VRM_1_0::Vrm vrm;
    VRMC_VRM_1_0::from_json(extensions["VRMC_vrm"], vrm);

    REQUIRE_FALSE(vrm.meta.version.empty());
    REQUIRE(vrm.meta.avatarPermission ==
            VRMC_VRM_1_0::Meta::AvatarPermissionType::OnlyAuthor);
  }
}

TEST_CASE("VRM 1.0 VRMC_springBone_extended_collider") {
  const auto src = nlohmann::json::parse(R"({
    "specVersion": "1.0",
    "shape": {
      "sphere": { "offset": [0, 0.1, 0], "radius": 0.5, "inside": true }
    }
  })");

  VRMC_VRM_1_0::SpringBoneExtendedCollider collider;
  VRMC_VRM_1_0::from_json(src, collider);

  REQUIRE(collider.specVersion == "1.0");
  REQUIRE(collider.shape.sphere.offset[1] == 0.1f);
  REQUIRE(collider.shape.sphere.radius == 0.5f);
  REQUIRE(collider.shape.sphere.inside);
  REQUIRE(collider.shape.plane.normal[2] == 1.f);

  nlohmann::json out;
  VRMC_VRM_1_0::to_json(out, collider);

  REQUIRE(out["specVersion"] == "1.0");
  REQUIRE(out["shape"]["sphere"]["radius"] == 0.5f);
  REQUIRE(out["shape"]["sphere"]["inside"] == true);
}

TEST_CASE("VRM 1.0 VRMC_vrm_animation") {
  const auto src = nlohmann::json::parse(R"({
    "specVersion": "1.0",
    "humanoid": {
      "humanBones": {
        "hips": { "node": 1 },
        "spine": { "node": 2 },
        "head": { "node": 3 },
        "leftUpperLeg": { "node": 4 },
        "leftLowerLeg": { "node": 5 },
        "leftFoot": { "node": 6 },
        "rightUpperLeg": { "node": 7 },
        "rightLowerLeg": { "node": 8 },
        "rightFoot": { "node": 9 },
        "leftUpperArm": { "node": 10 },
        "leftLowerArm": { "node": 11 },
        "leftHand": { "node": 12 },
        "rightUpperArm": { "node": 13 },
        "rightLowerArm": { "node": 14 },
        "rightHand": { "node": 15 },
        "leftThumbMetacarpal": { "node": 16 }
      }
    },
    "expressions": {
      "preset": {
        "happy": { "node": 20 }
      }
    },
    "lookAt": {
      "node": 30,
      "offsetFromHeadBone": [0, 0.06, 0]
    }
  })");

  VRMC_VRM_1_0::VrmAnimation anim;
  VRMC_VRM_1_0::from_json(src, anim);

  REQUIRE(anim.specVersion == "1.0");
  REQUIRE(anim.humanoid.humanBones.hips.node == 1);
  REQUIRE(anim.humanoid.humanBones.rightHand.node == 15);
  REQUIRE(anim.humanoid.humanBones.leftThumbMetacarpal.node == 16);
  REQUIRE(anim.expressions.preset.happy.node == 20);
  REQUIRE(anim.lookAt.node == 30);
  REQUIRE(anim.lookAt.offsetFromHeadBone[1] == 0.06f);

  nlohmann::json out;
  VRMC_VRM_1_0::to_json(out, anim);

  REQUIRE(out["specVersion"] == "1.0");
  REQUIRE(out["humanoid"]["humanBones"]["hips"]["node"] == 1);
  REQUIRE(out["expressions"]["preset"]["happy"]["node"] == 20);
  REQUIRE(out["lookAt"]["node"] == 30);
}

TEST_CASE("VRM 0.x (cgltf)") {
  cgltf_options options = {};
  cgltf_data *data = NULL;
  cgltf_result result =
      cgltf_parse_file(&options, "../data/0.x/001.vrm", &data);

  REQUIRE(result == cgltf_result_success);
  REQUIRE(data->data_extensions_count > 0);

  char *vrm_json = nullptr;
  for (cgltf_size i = 0; i < data->data_extensions_count; ++i) {
    if (strcmp(data->data_extensions[i].name, "VRM") == 0) {
      vrm_json = data->data_extensions[i].data;
      break;
    }
  }
  REQUIRE(vrm_json != nullptr);

  const nlohmann::json VRM_OBJ = nlohmann::json::parse(vrm_json);

  SECTION("load-001-extensions") {
    REQUIRE(VRM_OBJ.is_object());

    VRMC_VRM_0_0::Vrm vrm;
    VRMC_VRM_0_0::from_json(VRM_OBJ, vrm);

    REQUIRE_FALSE(vrm.specVersion.empty());
  }

  SECTION("load-001.meta") {
    REQUIRE(VRM_OBJ.is_object());
    REQUIRE(VRM_OBJ.contains("meta"));

    VRMC_VRM_0_0::Vrm vrm;
    VRMC_VRM_0_0::from_json(VRM_OBJ, vrm);

    REQUIRE_FALSE(vrm.meta.version.empty());
    REQUIRE(vrm.meta.allowedUserName ==
            VRMC_VRM_0_0::Meta::AllowedUserName::OnlyAuthor);
  }

  if (result == cgltf_result_success) {
    cgltf_free(data);
  }
}

TEST_CASE("VRM 1.0 (cgltf)") {
  cgltf_options options = {};
  cgltf_data *data = NULL;
  cgltf_result result =
      cgltf_parse_file(&options, "../data/1.0/001.vrm", &data);

  REQUIRE(result == cgltf_result_success);
  REQUIRE(data->data_extensions_count > 0);

  char *vrm_json = nullptr;
  for (cgltf_size i = 0; i < data->data_extensions_count; ++i) {
    if (strcmp(data->data_extensions[i].name, "VRMC_vrm") == 0) {
      vrm_json = data->data_extensions[i].data;
      break;
    }
  }
  REQUIRE(vrm_json != nullptr);

  const nlohmann::json VRM_OBJ = nlohmann::json::parse(vrm_json);

  SECTION("load-001-extensions") {
    REQUIRE(VRM_OBJ.is_object());

    VRMC_VRM_1_0::Vrm vrm;
    VRMC_VRM_1_0::from_json(VRM_OBJ, vrm);

    REQUIRE_FALSE(vrm.specVersion.empty());
  }

  SECTION("load-001.meta") {
    REQUIRE(VRM_OBJ.is_object());
    REQUIRE(VRM_OBJ.contains("meta"));

    VRMC_VRM_1_0::Vrm vrm;
    VRMC_VRM_1_0::from_json(VRM_OBJ, vrm);

    REQUIRE_FALSE(vrm.meta.version.empty());
    REQUIRE(vrm.meta.avatarPermission ==
            VRMC_VRM_1_0::Meta::AvatarPermissionType::OnlyAuthor);
  }

  if (result == cgltf_result_success) {
    cgltf_free(data);
  }
}
