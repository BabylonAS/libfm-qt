#include "filesysteminfojob.h"
#include "gobjectptr.h"

namespace Fm2 {

void FileSystemInfoJob::run() {
    GObjectPtr<GFileInfo> inf = GObjectPtr<GFileInfo>{
            g_file_query_filesystem_info(
                path_.gfile().get(),
                G_FILE_ATTRIBUTE_FILESYSTEM_SIZE","
                G_FILE_ATTRIBUTE_FILESYSTEM_FREE,
                cancellable().get(), nullptr),
            false
    };
    if(!inf)
        return;
    if(g_file_info_has_attribute(inf.get(), G_FILE_ATTRIBUTE_FILESYSTEM_SIZE)) {
        size_ = g_file_info_get_attribute_uint64(inf.get(), G_FILE_ATTRIBUTE_FILESYSTEM_SIZE);
        freeSize_ = g_file_info_get_attribute_uint64(inf.get(), G_FILE_ATTRIBUTE_FILESYSTEM_FREE);
        isAvailable_ = true;
    }
}

} // namespace Fm2