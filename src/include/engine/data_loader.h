#ifndef DATA_LOADER_H
#define DATA_LOADER_H
#include "../types/engine_options.h"


namespace hyperion::engine::services {
    class DataLoader {
        EngineOptions *_options;

    public:
        DataLoader(EngineOptions *options);
        void LoadData();
    };
}

#endif //DATA_LOADER_H
