#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utilities.h"

template<typename Derived, typename T>
class AssetManager
{
public:
    AssetManager(const std::string& pathsFile)
    {
        loadPaths(pathsFile);
    }

    virtual ~AssetManager()
    {
        purgeAssets();
    }

    /// Get an asset by id or return a null pointer
    T* getAsset(const std::string& id)
    {
        auto res = find(id);
        return (res ? res->first : nullptr);
    }

    /// Get a path to an asset by id or return an empty std::string
    std::string getPath(const std::string& id)
    {
        auto path = mPaths.find(id);
        return (path != mPaths.end() ? path->second : "");
    }

    /// Register the usage of an asset (and load it if necessary)
    /// to be sure it keeps being instantiated.
    bool requireAsset(const std::string &id)
    {
        auto res = find(id);
        // If asset exists, increment it's usage counter
        if(res) {
            ++res->second; // Increment asset instances counter
            return true;
        }
        // Else load asset if its path exists
        auto path = mPaths.find(id);
        // - No loading if there is no path
        if(path == mPaths.end())
            return false;
        // - Loading if there is path
        T* asset = load(path->second);
        if(!asset)
            return false;
        // If asset is loaded, put it in collection
        mAssets.emplace(id, std::make_pair(asset, 1));
        return true;
    }

    /// Deregister on usage af an asset.
    /// Unload asset if no more in use.
    bool releaseAsset(const std::string &id)
    {
        auto res = find(id);
        if(!res)
            return false;
        --res->second;
        // If no more instance of this asset, unload
        if(!res->second) {
            unload(id);
        }
        return true;
    }

    /// Unload all assets
    void purgeAssets()
    {
        while(mAssets.begin() != mAssets.end()) {
            delete mAssets.begin()->second.first;
            mAssets.erase(mAssets.begin());
        }
    }

    /// Load an asset by its path
    T* load(const std::string &path)
    {
        return static_cast<Derived*>(this)->load(path);
    }

private:
    std::unordered_map<std::string, std::pair<T*, unsigned int>> mAssets;
    std::unordered_map<std::string, std::string> mPaths;

    /// Find an asset in asset collection
    std::pair<T*, unsigned int>* find(const std::string &id)
    {
        if(mAssets.empty())
            return nullptr;
        auto itr = mAssets.find(id);
        return (itr != mAssets.end() ? &itr->second : nullptr);
    }

    /// Unload an asset by id
    bool unload(const std::string &id)
    {
        auto itr = mAssets.find(id);
        if(itr == mAssets.end())
            return false;
        delete itr->second.first;
        mAssets.erase(itr);
        return true;
    }

    /// Load paths to asset through a config file path
    void loadPaths(const std::string &pathFile)
    {
        std::ifstream paths;
        paths.open(Utils::getWorkingDirectory() + pathFile);
        if(paths.is_open()) {
            std::string line;
            while(std::getline(paths, line)) {
                std::stringstream keystream(line);
                std::string pathName;
                std::string path;
                keystream >> pathName;
                keystream >> path;
                mPaths.emplace(pathName, path);
            }
            paths.close();
            return;
        }
        // Error
        std::cerr << "Failed loading path file: " << pathFile << std::endl;
    }
};
