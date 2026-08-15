#include <gtest/gtest.h>
#include "Api.h"

TEST(RendererTest, TReadShaderFromFile) {
    Shader shader;
    std::string text = shader.ReadShaderFromFile("Testing.vert");
    EXPECT_EQ(text, "Testing\nRead");
}
