#pragma once

#include <hidapi.h>

#include <QObject>
#include <string>

class ProductInfo;

namespace mixxx {

namespace hid {

constexpr unsigned short kAppleVendorId = 0x5ac;

class DeviceInfo final {
  public:
    explicit DeviceInfo(
            const hid_device_info& device_info);

    unsigned short vendorId() const {
        return vendor_id;
    }
    unsigned short productId() const {
        return product_id;
    }
    /// The release number is stored as a binary-coded decimal (BCD)
    unsigned short releaseNumberBCD() const {
        return release_number;
    }

    const char* pathRaw() const {
        return m_pathRaw.c_str();
    }
    const wchar_t* serialNumberRaw() const {
        return m_serialNumberRaw.c_str();
    }

    const QString& manufacturerName() const {
        return m_manufacturerName;
    }
    const QString& productName() const {
        return m_productName;
    }
    const QString& serialNumber() const {
        return m_serialNumber;
    }

    bool isValid() const {
        return !productName().isNull() && !serialNumber().isNull();
    }

    QString formatInterface() const;
    QString formatUsage() const;
    QString formatName() const;

    bool matchProductInfo(
            const ProductInfo& productInfo) const;

  private:
    friend class DeviceCategory;
    friend QDebug operator<<(
            QDebug dbg,
            const DeviceInfo& deviceInfo);

    // members from hid_device_info
    unsigned short usage_page;
    unsigned short usage;
    int interface_number;
    unsigned short vendor_id;
    unsigned short product_id;
    unsigned short release_number;

    std::string m_pathRaw;
    std::wstring m_serialNumberRaw;

    QString m_manufacturerName;
    QString m_productName;
    QString m_serialNumber;
};

class DeviceCategory final : public QObject {
    // QObject needed for i18n device category
    Q_OBJECT
  public:
    static QString guessFromDeviceInfo(
            const DeviceInfo& deviceInfo) {
        return DeviceCategory().guessFromDeviceInfoImpl(deviceInfo);
    }

  private:
    QString guessFromDeviceInfoImpl(
            const DeviceInfo& deviceInfo) const;

    DeviceCategory() = default;
};

} // namespace hid

} // namespace mixxx
