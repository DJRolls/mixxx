#pragma once
/**
* @file controllerpresetfilehandler.h
* @author Sean Pappalardo spappalardo@mixxx.org
* @date Mon 9 Apr 2012
* @brief Handles loading and saving of Controller presets.
*
* The ControllerPresetFileHandler is used for serializing/deserializing the
* ControllerPreset objects to/from XML files and is also responsible
* finding the script files that belong to a preset in the file system.
*
* Subclasses can implement the private load function to add support for XML
* elements that are only useful for certain mapping types.
*/

#include "util/xml.h"
#include "controllers/controllerpreset.h"

class ControllerPresetFileHandler {
  public:
    ControllerPresetFileHandler() {};
    virtual ~ControllerPresetFileHandler() {};

    static ControllerPresetPointer loadPreset(const QFileInfo& presetFile,
            const QDir& systemPresetsPath);

    /** Overloaded function for convenience
     *
     * @param path The path to a controller preset XML file.
     * @param deviceName The name/id of the controller
     */
    ControllerPresetPointer load(const QString path,
            const QString deviceName,
            const QDir& systemPresetsPath);

    // Returns just the name of a given device (everything before the first
    // space)
    QString rootDeviceName(QString deviceName) const {
        return deviceName.left(deviceName.indexOf(" "));
    }

  protected:
    QDomElement getControllerNode(const QDomElement& root,
                                  const QString deviceName);

    void parsePresetInfo(const QDomElement& root,
                         ControllerPreset* preset) const;

    /** Adds script files from XML to the ControllerPreset.
     *
     * This function parses the supplied QDomElement structure, finds the
     * matching script files inside the search paths and adds them to
     * ControllerPreset.
     *
     * @param root The root node of the XML document for the preset.
     * @param deviceName The name/id of the controller.
     * @param preset The ControllerPreset these scripts belong to.
     */
    void addScriptFilesToPreset(const QDomElement& root,
            ControllerPreset* preset,
            const QDir& systemPresetsPath) const;

    // Creates the XML document and includes what script files are currently
    // loaded. Sub-classes need to call this before adding any other items.
    QDomDocument buildRootWithScripts(const ControllerPreset& preset,
                                      const QString deviceName) const;

    bool writeDocument(QDomDocument root, const QString fileName) const;

  private:
    // Sub-classes implement this.
    virtual ControllerPresetPointer load(const QDomElement root,
            const QString filePath,
            const QString deviceName,
            const QDir& systemPresetPath) = 0;
};
