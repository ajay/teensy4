#include <iomanip>
#include <iostream>
#include <limits>

#include "Arduino.h"
#include "MatrixHardware_Teensy4_ShieldV5.h"
#include "SmartMatrix.h"

// based off MultipleTextLayers example from SmartMatrix

#define COLOR_DEPTH 24
// constexpr size_t kColorDepth = 24;

template<class T>
class SweepValue final
{
  public:
    SweepValue(T value = 0, T min = T(), T max = std::numeric_limits<T>::max(), T step = 1,
               bool increasing = true)
        : value_{value},
          min_{min},
          max_{max},
          step_{step},
          increasing_{(value_ != min_) ? increasing : false}
    {
    }

    T step()
    {
        if((value_ <= min_) || (value_ >= max_))
        {
            increasing_ = !increasing_;
        }

        value_ += increasing_ ? step_ : -step_;
        return value();
    }

    T value()
    {
        return value_;
    }

  private:
    T    value_;
    T    min_;
    T    max_;
    T    step_;
    bool increasing_ = true;
};

int main()
{
    Serial.begin(115200);

    constexpr size_t kMatrixWidth           = 32;
    constexpr size_t kMatrixHeight          = 32;
    constexpr size_t kRefreshDepth          = 48;
    constexpr size_t kDmaBufferRows         = 4;
    constexpr size_t kPanelType             = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;
    constexpr size_t kMatrixOptions         = (SM_HUB75_OPTIONS_NONE);
    constexpr size_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

    SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows,
                                 kPanelType, kMatrixOptions);
    SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(layer1, kMatrixWidth, kMatrixHeight, COLOR_DEPTH,
                                         kScrollingLayerOptions);

    matrix.addLayer(&layer1);
    matrix.begin();

    SweepValue<size_t>  layer1Speed{0, 0, 150};
    SweepValue<uint8_t> red{100};
    SweepValue<uint8_t> green{100};
    SweepValue<uint8_t> blue{100};

    layer1.setMode(wrapForward);
    layer1.setColor({red.value(), green.value(), blue.value()});
    layer1.setSpeed(layer1Speed.value());
    layer1.setFont(gohufont11b);
    layer1.setOffsetFromTop((kMatrixHeight / 2) - 5);
    layer1.start("Hello world", -1);

    size_t counter = 0;
    while(true)
    {
        delay(1);
        ++counter;

        if(!(counter % 10))
        {
            layer1.setSpeed(layer1Speed.step());
            layer1.setColor({red.value(), green.value(), blue.value()});
        }

        if(!(counter % 20))
        {
            red.step();
        }

        if(!(counter % 30))
        {
            green.step();
        }

        if(!(counter % 40))
        {
            blue.step();
        }

        if(!(counter % 1000))
        {
            std::cout << (counter / 1000) << " Refresh rate: " << matrix.getRefreshRate() << '\n';
        }
    }
}
