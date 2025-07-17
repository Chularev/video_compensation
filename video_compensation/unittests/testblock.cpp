#include "testblock.h"
#include "block.h"

TEST(TestBlock, Equal) {

    Block block1(0,0);
    for (int i = 0; i < block1.side(); i++)
        for (int j = 0; j < block1.side(); j++)
        {

            Pixel pixel;
            pixel.setCoordX(rand() % 100);
            pixel.setCoordY(rand() % 100);

            size_t lumaIndex = static_cast<size_t>(rand() % 100);
            pixel.setY(rand() % 100);
            pixel.setLumaCoord(lumaIndex);

            size_t chromaIndex = static_cast<size_t>(rand() % 100);
            pixel.setChromaCoord(chromaIndex);

            pixel.setU(rand() % 100);
            pixel.setV(rand() % 100);

            block1(i,j) = pixel;
        }

    Block block2(0,0);
    EXPECT_FALSE(block1 == block2);

   // EXPECT_EQ(5, calc.Add(2, 3));
    //EXPECT_EQ(-1, calc.Add(2, -3));
}
