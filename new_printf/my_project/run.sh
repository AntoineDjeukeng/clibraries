#!/bin/bash

# Exit on error
set -e

echo "🔨 Building project..."
make

echo "🧪 Running with Valgrind..."
make valgrind

echo "🧹 Cleaning up build files..."
make clean

echo "✅ Done!"
