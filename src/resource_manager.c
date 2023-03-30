#include "src/resource_manager.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

radiant_resource_manager_create_result_t radiant_resource_manager_create(
    const char* root_dir) {
  radiant_resource_manager_create_result_t result = {
      .manager = {0},
      .succeeded = true,
  };
  radiant_resource_manager_t* manager = &result.manager;

  if (root_dir) {
    manager->root_dir = strdup(root_dir);
  } else {
    manager->root_dir = strdup(".");
  }
  if (!manager->root_dir) {
    result.succeeded = false;
    return result;
  }

  return result;
}

void radiant_resource_manager_destroy(radiant_resource_manager_t manager) {
  free(manager.root_dir);
}

radiant_file_result_t radiant_resource_manager_open(
    radiant_resource_manager_t manager,
    const char* relative_path) {
  if (!relative_path || strlen(relative_path) == 0) {
    return (radiant_file_result_t){
        .succeeded = false,
    };
  }

  uint64_t filename_size = strlen(manager.root_dir) + strlen(relative_path);
  if (relative_path[0] != '/') {
    filename_size += 1;
  }
  // Add 1 for the \0.
  filename_size += 1;

  char* filename = (char*)malloc(filename_size);
  snprintf(filename, filename_size, "%s%s%s", manager.root_dir,
           (relative_path[0] == '/' ? "" : "/"), relative_path);

  radiant_file_result_t file_result = radiant_file_open(filename);
  free(filename);

  return file_result;
}
