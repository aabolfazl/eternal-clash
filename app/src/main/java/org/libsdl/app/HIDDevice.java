package org.libsdl.app;

import android.hardware.usb.UsbDevice;

interface HIDDevice
{
    int getId();
    int getVendorId();
    int getProductId();
    String getSerialNumber();
    int getVersion();
    String getManufacturerName();
    String getProductName();
    UsbDevice getDevice();
    boolean open();
    int writeReport(byte[] report, boolean feature);
    boolean readReport(byte[] report, boolean feature);
    void setFrozen(boolean frozen);
    void close();
    void shutdown();
}
