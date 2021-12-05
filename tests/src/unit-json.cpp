#include <catch2/catch.hpp>
#include <filesystem>
#include <fx/gltf.h>

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
