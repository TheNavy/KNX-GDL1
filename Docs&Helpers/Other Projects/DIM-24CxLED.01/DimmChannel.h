#pragma once

#include <KonnektingDevice.h>
#include "HardwareChannel.h"
#include "HardwareChannel_mega8.h"
#include "HardwareChannel_pca9685.h"
#include "config.h"


class DimmChannel
{
	public: virtual void KnxEvent(byte index) = 0;
	
	public: virtual void Cyclic() = 0;

  public: virtual void Shutdown() = 0;

  public: virtual void Refresh() = 0;
};