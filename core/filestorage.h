#pragma once
#include "husarnet.h"
#include "configmanager.h"

namespace FileStorage {

inline const std::string idFilePath(const std::string configDir) { return configDir + "id"; }
inline const std::string httpSecretFilePath(const std::string configDir) { return configDir + "http_secret"; }
inline const std::string settingsFilePath(const std::string configDir) { return configDir + "settings.json"; }
inline const std::string licenseFilePath(const std::string configDir) { return configDir + "license.json"; }
inline const std::string controlSocketPath(const std::string configDir) { return configDir + "control.sock"; }

std::ifstream openFile(std::string name);
Identity* readIdentity(std::string configDir);
void generateAndWriteId(std::string configDir);
void generateAndWriteHttpSecret(std::string configDir);
std::string readHttpSecret(std::string configDir);
std::string generateRandomString(const int length);

}
