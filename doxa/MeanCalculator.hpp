// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef MEANCALCULATOR_HPP
#define MEANCALCULATOR_HPP

#include <vector>
#include "Types.hpp"
#include "LocalWindow.hpp"
#include "Region.hpp"


namespace Doxa
{
	typedef std::vector<int64_t> IntegralImage;

	/// <summary>
	/// A fast integral image based calculator for calculating the Mean.
	/// It is largely inspired by Shafait, but deviates from the reference implementation.
	/// This deviation should greatly improve the performance for Mean-only calcuations.
	/// </summary>
	class MeanCalculator
	{
	public:
		MeanCalculator() :
			integral_image(0),
			imageWidth(0)
		{}

		void Initialize(const Image& grayScaleImage)
		{
			integral_image.resize(grayScaleImage.size);
			imageWidth = grayScaleImage.width;

			BuildIntegralImage(integral_image, grayScaleImage);
		}

		inline void CalculateMean(double& mean, const Region& window) const
		{
			// Note: This data type has a large impact on performance.
			double diff;
			CalculateDiff(diff, window);

			// Get the Mean using our Shafait inspired algorithm
			const int area = window.Area();
			mean = diff / area;
		}

	protected:
		inline void CalculateDiff(double& diff, const Region& window) const
		{
			const int xmax_ymax = (window.bottomRight.y * imageWidth) + window.bottomRight.x;

			if (window.upperLeft.x)
			{
				const int xmin_ymax = (window.bottomRight.y * imageWidth) + (window.upperLeft.x - 1);

				if (window.upperLeft.y)
				{
					const int xmax_ymin = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;
					const int xmin_ymin = ((window.upperLeft.y - 1) * imageWidth) + (window.upperLeft.x - 1);

					diff = (integral_image[xmax_ymax] + integral_image[xmin_ymin]) - (integral_image[xmax_ymin] + integral_image[xmin_ymax]);
				}
				else
				{
					diff = integral_image[xmax_ymax] - integral_image[xmin_ymax];
				}
			}
			else
			{
				if (window.upperLeft.y)
				{
					const int xmax_ymin = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;

					diff = integral_image[xmax_ymax] - integral_image[xmax_ymin];
				}
				else
				{
					diff = integral_image[xmax_ymax];
				}
			}
		}

		void BuildIntegralImage(IntegralImage& integralImage, const Image& grayScaleImage)
		{
			int row;
			int cell;

			integralImage[0] = grayScaleImage.data[0];

			for (int y = 1; y < grayScaleImage.height; ++y)
			{
				row = (y * grayScaleImage.width);
				integralImage[row] = integralImage[row - grayScaleImage.width] + grayScaleImage.data[row];
			}

			for (int x = 1; x < grayScaleImage.width; ++x)
			{
				integralImage[x] = integralImage[x - 1] + grayScaleImage.data[x];
			}

			for (int y = 1; y < grayScaleImage.height; ++y)
			{
				row = (y * grayScaleImage.width);
				int rowSum = grayScaleImage.data[row];

				for (int x = 1; x < grayScaleImage.width; ++x)
				{
					cell = row + x;

					integralImage[cell] = integralImage[cell - grayScaleImage.width] + rowSum + grayScaleImage.data[cell];

					rowSum += grayScaleImage.data[cell];
				}
			}
		}

		IntegralImage integral_image;
		int imageWidth;
	};
}


#endif //MEANCALCULATOR_HPP
