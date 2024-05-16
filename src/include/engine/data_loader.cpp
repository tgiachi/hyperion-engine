//
// Created by squid on 5/16/24.
//

#include "data_loader.h"

#include <spdlog/spdlog.h>


namespace hyperion::engine::services {
    DataLoader::DataLoader(EngineOptions *options) {
        this->_options = options;
        spdlog::info("Data directory: {}", this->_options->dataDirectory);
    }

    void DataLoader::LoadData() {

    }
}
