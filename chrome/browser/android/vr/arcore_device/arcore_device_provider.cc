// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/android/vr/arcore_device/arcore_device_provider.h"

#include "chrome/browser/android/vr/arcore_device/arcore_device.h"
#include "chrome/browser/android/vr/arcore_device/arcore_shim.h"

namespace device {

ArCoreDeviceProvider::ArCoreDeviceProvider() = default;

ArCoreDeviceProvider::~ArCoreDeviceProvider() = default;

void ArCoreDeviceProvider::Initialize(
    base::RepeatingCallback<void(mojom::XRDeviceId,
                                 mojom::VRDisplayInfoPtr,
                                 mojom::XRRuntimePtr)> add_device_callback,
    base::RepeatingCallback<void(mojom::XRDeviceId)> remove_device_callback,
    base::OnceClosure initialization_complete) {
  if (vr::SupportsArCore())
    arcore_device_ = std::make_unique<ArCoreDevice>();
  if (arcore_device_) {
    add_device_callback.Run(arcore_device_->GetId(),
                            arcore_device_->GetVRDisplayInfo(),
                            arcore_device_->BindXRRuntimePtr());
  }
  initialized_ = true;
  std::move(initialization_complete).Run();
}

bool ArCoreDeviceProvider::Initialized() {
  return initialized_;
}

}  // namespace device
