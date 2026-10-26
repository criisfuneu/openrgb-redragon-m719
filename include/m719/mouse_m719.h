#ifndef MOUSE_M719_H
#define MOUSE_M719_H

#include "RGBController.h"
#include <hidapi/hidapi.h>
#include <string>

class RGBController_M719 : public RGBController
{
public:
    RGBController_M719(hid_device* dev_handle, const char* path);
    ~RGBController_M719();

    void        SetupZones();
    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();

private:
    hid_device* dev;
    std::string location;
};

#endif // MOUSE_M719_H
