# :diamond_shape_with_a_dot_inside: VRM.h

C++ header-only library for simple serialization/deserialization of [VRM](https://vrm.dev/en/) on top of [fx-gltf](https://github.com/jessey-git/fx-gltf).

## Features

- [x] Supports both VRM 0.x and 1.0 specification
- [x] Full serialization and deserialization capability

## Usage

### VRM 0.x

```cpp
#define USE_VRMC_VRM_0_0 // Enable VRM 1.0
#include <VRMC/VRM.h> // Single header

std::filesystem::path f{"model.vrm"};
const auto doc = fx::gltf::LoadFromBinary(f);
const auto extensions = doc.extensionsAndExtras["extensions"];

VRMC_VRM_0_0::Vrm vrm;
VRMC_VRM_0_0::from_json(extensions["VRM"], vrm);

if (vrm.meta.allowedUserName == VRMC_VRM_0_0::Meta::AllowedUserName::OnlyAuthor) {
	// ...
}
```

### VRM 1.0

```cpp
#define USE_VRMC_VRM_1_0 // Enable VRM 1.0
#include <VRMC/VRM.h> // Single header

std::filesystem::path f{"model.vrm"};
const auto doc = fx::gltf::LoadFromBinary(f);
const auto extensions = doc.extensionsAndExtras["extensions"];

VRMC_VRM_1_0::Vrm vrm;
VRMC_VRM_1_0::from_json(extensions["VRMC_vrm"], vrm);

if (vrm.meta.avatarPermission == VRMC_VRM_1_0::Meta::AvatarPermissionType::OnlyAuthor) {
	// ...
}
```

## License

* Available to anybody free of charge, under the terms of MIT License (see LICENSE).

## Run unit tests

You need [Cmake](https://cmake.org/download/) and Visual Studio with C++ environment installed. There is a CMakeLists.txt file which has been tested with [Cmake](https://cmake.org/download/) on Windows. For instance in order to generate a Visual Studio 10 project, run cmake like this:


```
> cd tests
> mkdir build; cd build
> cmake -G "Visual Studio 10" ..
```

