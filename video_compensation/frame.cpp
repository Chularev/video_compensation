#include "frame.h"

#include <frameinfo.h>
#include <stdexcept>
#include <x86intrin.h>
#include <iostream>

Frame::Frame(const std::vector<char> &dataY, const std::vector<char> &dataU, const std::vector<char> &dataV, int index)
    : dataY_(dataY), dataU_(dataU), dataV_(dataV),  index_(index)
{

}

int Frame::index() const
{
    return index_;
}

std::vector<char> Frame::dataY() const
{
    return dataY_;
}

std::vector<char> Frame::dataV() const
{
    return dataV_;
}

std::vector<char> Frame::dataU() const
{
    return dataU_;
}

Pixel Frame::getPixel(int coordX, int coordY) const
{
    if (coordX < 0 || coordX >= FrameInfo::getWidth())
        throw std::out_of_range("invalid coordinate X");

    if (coordY < 0 || coordY >= FrameInfo::getHeight())
      throw std::out_of_range("invalid coordinate Y");

    Pixel pixel;
    pixel.setCoordX(coordX);
    pixel.setCoordY(coordY);

    size_t lumaIndex = static_cast<size_t>(FrameInfo::getWidth() * coordY + coordX);
    pixel.setY(dataY_[lumaIndex]);
    pixel.setLumaCoord(lumaIndex);

    size_t chromaIndex = static_cast<size_t>((FrameInfo::getWidth() / 2) * (coordY /2) + coordX / 2);
    pixel.setChromaCoord(chromaIndex);

    pixel.setU(dataU_[chromaIndex]);
    pixel.setV(dataV_[chromaIndex]);

    return pixel;
}

void Frame::setPixel(const Pixel &pixel)
{

    if (pixel.getCoordX() < 0 || pixel.getCoordX() >= FrameInfo::getWidth())
        throw std::out_of_range("invalid coordinate X");

    if (pixel.getCoordY() < 0 || pixel.getCoordY() >= FrameInfo::getHeight())
      throw std::out_of_range("invalid coordinate Y");

    dataY_[pixel.getLumaCoord()] = pixel.getY();
    dataU_[pixel.getChromaCoord()] = pixel.getU();
    dataV_[pixel.getChromaCoord()] = pixel.getV();
}

void _mesa_streaming_load_memcpy(void *__restrict  dst, void *__restrict  src, size_t len)
{
   char *__restrict d = (char*) dst;
   char *__restrict s = (char*) src;
   /* If dst and src are not co-aligned, fallback to memcpy(). */
   if (((uintptr_t)d & 15) != ((uintptr_t)s & 15)) {
      memcpy(d, s, len);
      return;
   }
   /* memcpy() the misaligned header. At the end of this if block, <d> and <s>
    * are aligned to a 16-byte boundary or <len> == 0.
    */
   if ((uintptr_t)d & 15) {
      uintptr_t bytes_before_alignment_boundary = 16 - ((uintptr_t)d & 15);
      //assert(bytes_before_alignment_boundary < 16);
  //    memcpy(d, s, MIN2(bytes_before_alignment_boundary, len));
//      d = (char *)ALIGN((uintptr_t)d, 16);
//      s = (char *)ALIGN((uintptr_t)s, 16);
//      len -= MIN2(bytes_before_alignment_boundary, len);
   }
   if (len >= 64)
      _mm_mfence();
   while (len >= 64) {
      __m128i *dst_cacheline = (__m128i *)d;
      __m128i *src_cacheline = (__m128i *)s;
      __m128i temp1 = _mm_stream_load_si128(src_cacheline + 0);
      __m128i temp2 = _mm_stream_load_si128(src_cacheline + 1);
      __m128i temp3 = _mm_stream_load_si128(src_cacheline + 2);
      __m128i temp4 = _mm_stream_load_si128(src_cacheline + 3);
      _mm_store_si128(dst_cacheline + 0, temp1);
      _mm_store_si128(dst_cacheline + 1, temp2);
      _mm_store_si128(dst_cacheline + 2, temp3);
      _mm_store_si128(dst_cacheline + 3, temp4);
      d += 64;
      s += 64;
      len -= 64;
   }
   /* memcpy() the tail. */
   if (len) {
      memcpy(d, s, len);
   }
}

Block Frame::getBlock(int topLeftX, int topLeftY) const
{
    Block block(topLeftX,topLeftY);

    char a[16];
    char b[16];
     for (int i =0; i < 16; i++)
           b[i]  = i;

     //__m128i *dst_cacheline = (__m128i *)a;
     __m128i *src_cacheline = (__m128i *)b;

     __asm__ volatile
      (
       "movups %[a], %%xmm0\n\t"	// поместить 4 переменные с плавающей точкой из a в регистр xmm0
       "movups %[b], %%xmm1\n\t"	// поместить 4 переменные с плавающей точкой из b в регистр xmm1
       "MOVNTDQA %[src],%%xmm0\n\t"
       "movdqa %%xmm0, %[a]\n\t"	// выгрузить результаты из регистра xmm0 по адресам a
       :
       : [a]"m"(*a), [b]"m"(*b), [src]"m"(*src_cacheline)
       : "%xmm0", "%xmm1"
      );

     for (int i=0; i <8; i++)
        std::cout << static_cast<int>(a[i]) << std:: endl;

    return block;
}
