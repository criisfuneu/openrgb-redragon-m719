#include "mouse_m719.h"

RGBController_M719::RGBController_M719(hid_device* dev_handle, const char* path)
{
    dev         = dev_handle;
    location    = path;

    name        = "Redragon M719 Invader RGB";
    vendor      = "Redragon";
    type        = DEVICE_TYPE_MOUSE;
    description = "Redragon M719 Gaming Mouse";

    rgb_mode mode;
    mode.name       = "Direct";
    mode.value      = 0;
    mode.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    mode.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(mode);

    SetupZones();
}

RGBController_M719::~RGBController_M719()
{
    if(dev)
    {
        hid_close(dev);
    }
}

void RGBController_M719::SetupZones()
{
    zone m719_zone;
    m719_zone.name       = "Mouse Zone";
    m719_zone.type       = ZONE_TYPE_LINEAR;
    m719_zone.leds_min   = 1;
    m719_zone.leds_max   = 7;
    m719_zone.leds_count = 7;
    m719_zone.matrix_map = NULL;
    zones.push_back(m719_zone);

    leds.resize(7);
    for(size_t i = 0; i < leds.size(); i++)
    {
        leds[i].name = "LED " + std::to_string(i + 1);
    }

    SetupColors();
}

void RGBController_M719::ResizeZone(int zone, int new_size)
{
    (void)zone;
    (void)new_size;
}

void RGBController_M719::DeviceUpdateLEDs()
{
    unsigned char buf[9] = { 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    if(colors.size() > 0)
    {
        buf[3] = RGBGetRValue(colors[0]);
        buf[4] = RGBGetGValue(colors[0]);
        buf[5] = RGBGetBValue(colors[0]);
    }

    if(dev)
    {
        hid_write(dev, buf, sizeof(buf));
    }
}

void RGBController_M719::UpdateZoneLEDs(int zone)
{
    (void)zone;
    DeviceUpdateLEDs();
}

void RGBController_M719::UpdateSingleLED(int led)
{
    (void)led;
    DeviceUpdateLEDs();
}

void RGBController_M719::DeviceUpdateMode()
{
    DeviceUpdateLEDs();
}
