#ifndef DATA_LOADER_H
#define DATA_LOADER_H
#include "../types/engine_options.h"


namespace hyperion::engine::services {
    class DataLoader {
    public:
        void LoadData(EngineOptions &options);
    };
}

#endif //DATA_LOADER_H
