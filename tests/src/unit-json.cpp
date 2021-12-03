#include <catch2/catch.hpp>
#include <filesystem>
#include <iostream>

#define USE_VRMC_VRM_0_0
#define USE_VRMC_VRM_1_0
#include <VRMC/VRM.h>

TEST_CASE("VRM 0.x") {
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

TEST_CASE("VRM 1.0") {
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
      REQUIRE(vrm.meta.avatarPermission == VRMC_VRM_1_0::Meta::AvatarPermissionType::OnlyAuthor);
  }

}
