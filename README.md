# video_compensation
Тестовое задание.

Имеются два изображения любого размера в формате yuv420p (Если не получится взять из настоящей видео последовательности, то заполнить случайными числами). Для каждого блока 8х8(или 16х16) пикселей из второго изображения имеется вектор движения (задать произвольно). Сделать компенсацию движения.

Минимум: Программа на С++ (приветствуется С++11, максимум С++14) поблочно (блоки 8х8 или 16х16, слева направо, сверху вниз) читает данные из второго изображения; по вектору движения находит соответствующий блок и читает данные из первого изображения; производит попиксельное вычитание первого блока из второго. Т.е. производится компенсация движения. Результат вычитания (блок 8х8 или 16x16) записывается поблочно в третье изображение в соответствующую позицию.

Дополнительные задания:

Процедура чтения блока 8х8 из кадра написана на ASM с использованием SIMD инструкций (2 балла).

Процедура компенсации написана на ASM с использованием SIMD инструкций (2 балл).
В качестве исходных данных взята настоящая видео последовательность из файл в формате yuv420p, т.е. программа производит поиск и компенсацию движения для всех кадров последовательности (2 балла).

Реализовать простой поиск движения в радиусе 16 пикселей (например полный поиск) (2 балл).

Процедура сравнивания блоков написана на ASM с использованием SIMD инструкций (2 балл).

Реализовать оптимизированный поиск движения (алгоритм на ваше усмотрение) (3 балла).
Реализовать полупиксельный поиск движения дополнительно к основному в радиусе пол пикселя от найденного вектора (3 балла).

Посчитать PSNR метрику двух изображений (1 балла).

Распараллелить алгоритм поиска или компенсации движения(2 балла).

Можно делать любые пункты на выбор. Чем больше будет реализовано - тем лучше.
