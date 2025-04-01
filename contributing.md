# How to contribute code
This is the process that you should follow when contributing to this repository.

1. Create a new branch named after the feature or change you plan to implement. Ex. **brake-lights-implementation**
2. Commit changes to branch (ensure your code is clang-formatted; see [Using clang-format](#using-clang-format) for instructions)
3. Make a PR to request your changes be merged into main and wait for it to be reviewed by another team member before a merging.

# Using clang-format
To ensure consistent code formatting, we use clang-format. Please follow the instructions below to format your code before committing changes.

## Installing clang-format
1. Install clang-format on your system. You can find installation instructions for your platform [here](https://clang.llvm.org/docs/ClangFormat.html).

## Formatting code
1. To format a single file, run the following command:
   ```
   clang-format -i <filename>
   ```
2. To format all files in the repository, run the following command:
   ```
   find . -name "*.ino" -o -name "*.cpp" -o -name "*.h" | xargs clang-format -i
   ```

## Additional information
- Make sure to format your code before committing changes to ensure consistency across the codebase.
- If you encounter any issues with clang-format, please refer to the [clang-format documentation](https://clang.llvm.org/docs/ClangFormat.html) or reach out to a team member for assistance.
