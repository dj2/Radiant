#pragma once

#include "src/io.h"

typedef struct radiant_resource_manager_t {
  char* root_dir;
} radiant_resource_manager_t;

/// Result of creating a resource manager
typedef struct radiant_resource_manager_create_result_t {
  /// The resource manager handle. Only valid if |succeeded| is true.
  radiant_resource_manager_t manager;
  /// True if the manager was successfully created. False otherwise.
  bool succeeded;
  /// Unused padding
  RADIANT_PAD(7);
} radiant_resource_manager_create_result_t;

/// Creates a resource manager which will load files relative to |root_dir|
radiant_resource_manager_create_result_t radiant_resource_manager_create(
    const char* root_dir);
/// Destroys the resource manager
void radiant_resource_manager_destroy(radiant_resource_manager_t manager);

/// Opens the file at |relative_path| to the |manager.root_dir|. The caller is
/// responsible for maintaining the resulted file handle and must call the
/// appropriate methods to close the file.
radiant_file_result_t radiant_resource_manager_open(
    radiant_resource_manager_t manager,
    const char* relative_path);
