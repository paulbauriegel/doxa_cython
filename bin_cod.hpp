// Δoxa Binarization Framework Demo
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#include <iostream>
#include <algorithm>
#include "Doxa/Image.hpp"
#include "Doxa/PNM.hpp"
#include "Doxa/Otsu.hpp"
#include "Doxa/Bernsen.hpp"
#include "Doxa/Niblack.hpp"
#include "Doxa/Sauvola.hpp"
#include "Doxa/Wolf.hpp"
#include "Doxa/Nick.hpp"
#include "Doxa/Gatos.hpp"
#include "Doxa/Su.hpp"
#include "Doxa/TRSingh.hpp"
#include "Doxa/Wan.hpp"
#include "Doxa/ISauvola.hpp"

using namespace std;
using namespace Doxa;

enum BinarizeMethod { 
    otsu,
    bernsen,
    niblack,
    sauvola,
    wolf,
    nick,
    gatos,
    su,
    trsingh,
    wan,
    isauvola
};

class Binarize{
    public:
        Binarize();
    static void transform(std::string source, BinarizeMethod m, std::string output){
        const Image image = PNM::Read(source);

        int w = 0;
        int g = 0;
        double k = 0.0;
        Parameters parameters({ { "window", w == 0 ? 75 : w } });
        Image binaryImage;
        switch(m)
        {
            case otsu:
                binaryImage = Otsu::ToBinaryImage(image, parameters);
                break;
            case bernsen:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                binaryImage = Bernsen::ToBinaryImage(image, parameters);
                break;
            case niblack:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                binaryImage = Niblack::ToBinaryImage(image, parameters);
                break;
            case sauvola:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                binaryImage = Sauvola::ToBinaryImage(image, parameters);
                break;
            case wolf:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                binaryImage = Wolf::ToBinaryImage(image, parameters);
                break;
            case nick:
                parameters.Set("k", k == 0.0 ? -0.2 : k);
                binaryImage = Nick::ToBinaryImage(image, parameters);
                break;
            case gatos:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                parameters.Set("glyph", g == 0 ? 60 : g);
                binaryImage = Gatos::ToBinaryImage(image, parameters);
                break;
            case su:
                binaryImage = Su::ToBinaryImage(image, parameters);
                break;
            case trsingh:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                binaryImage = TRSingh::ToBinaryImage(image, parameters);
                break;
            case wan:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                binaryImage = Wan::ToBinaryImage(image, parameters);
                break;
            case isauvola:
                parameters.Set("k", k == 0.0 ? 0.2 : k);
                binaryImage = ISauvola::ToBinaryImage(image, parameters);
                break;
            default:
                binaryImage = Su::ToBinaryImage(image, parameters);
                break;
        
        }
        PNM::Write(binaryImage, output + "-Bin.pbm");
    }
};