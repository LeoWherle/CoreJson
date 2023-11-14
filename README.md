# JSON Parser & Builder Library in C

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## Features

- **Parsing**: Easily parse JSON data from strings or files.
- **Building**: Create JSON structures programmatically with a fluent API.
- **Error Handling**: Robust error handling with descriptive error messages.
- **Performance**: Efficient parsing and building for improved application speed.
- **Memory Management**: Careful memory management to avoid memory leaks.

## Requirements

- C99 compiler
- from libc [malloc, reallocarray, calloc, free, memcpy, memset, strlen, dprintf, strncmp *for debugging = fprintf*]

## Table of Contents

- [Usage](#usage)
  - [Parsing JSON](#parsing-json)
  - [Building JSON](#building-json)
- [Error Handling](#error-handling)
- [Examples](#examples)
- [License](#license)

## Usage

### Parsing JSON

```c
#include "corejson.h"

int main() {
    const char* json_data = "{ \"name\": \"John\", \"age\": 30 }";
    json_value_t *json = NULL;

    // Parse JSON from string
    json = jsn_parse(json_data);
    if (json == NULL) {
        fprintf(stderr, "Error: Failed to parse JSON\n");
        return 1;
    }
    // Print JSON to stdout (could be a file)
    jsn_print(json, JSN_FORMAT_SPACES, STDOUT_FILENO);
    jsn_free(json);
    return 0;
    
}
```

### Building JSON

```c
#include "corejson.h"
#include "corejson/builder.h"

int main() {
    int ret = 0;
    // Create a JSON object
    json_value_t *value = NULL;

    value = jsn_object_create();
    if (value == NULL) {
        fprintf(stderr, "Error: Failed to create JSON object\n");
        return 1;
    }
    ret = jsn_object_add_number(object, "number", 42);
    if (ret == JSN_ERROR) {
        fprintf(stderr, "Error: Failed to add number to JSON object\n");
        jsn_free(value);
        return 1;
    }
    ret = jsn_object_add_string(object, "string", "Hello, World!");
    if (ret == JSN_ERROR) {
        fprintf(stderr, "Error: Failed to add string to JSON object\n");
        jsn_free(value);
        return 1;
    }
    /*
    ** The JSON object now looks like this:
    ** {
    **     "number": 42,
    **     "string": "Hello, World!"
    ** }
    */
    jsn_free(value);
    return 0;
}
```

## Examples

Check the [examples](examples/) directory for more detailed usage examples.

## License

This project is licensed under the [MIT License](LICENSE).