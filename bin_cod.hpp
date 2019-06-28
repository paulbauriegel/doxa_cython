#ifndef BINARIZE_H
#define BINARIZE_H

#include <string>
#include <iostream>
#include <algorithm>
#include "Image.hpp"
#include "PNM.hpp"
#include "Otsu.hpp"
#include "Bernsen.hpp"
#include "Niblack.hpp"
#include "Sauvola.hpp"
#include "Wolf.hpp"
#include "Nick.hpp"
#include "Gatos.hpp"
#include "Su.hpp"
#include "TRSingh.hpp"
#include "Wan.hpp"
#include "ISauvola.hpp"

using namespace std;
using namespace Doxa;

namespace binarize {

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
        PNM::Write(binaryImage, output);
    }

}

#endif