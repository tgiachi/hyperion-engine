//
// Created by squid on 5/16/24.
//

#include "data_loader.h"

#include <spdlog/spdlog.h>


namespace hyperion::engine::services {
    void DataLoader::LoadData(EngineOptions &options) {
        spdlog::info("Loading data from {}", options.dataDirectory);
    }
}
