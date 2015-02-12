/// This class is used to store media (images, music etc.) as well as
/// the filename associated with them.
/// This allows the media to be unloaded and reloaded at runtime
/// without having to hard-code the filename multiple times
#ifndef ASSET_H
#define ASSET_H
#include <string>


template <class T>
class Asset
{
    friend class Actor;
    friend class AssetManager;

	public:
		// This constructor is used for assets that will not be displayed on the screen
        // such as sounds. The x, y, z and scale variables are set to -1 so that if the
        // was rendered and no errors were thrown, it wouldn't be seen.
        //template <class T>
        Asset(T _item, std::string _filename)
        {
            item = _item;
            filename = _filename;
            x = -1;
            y = -1;
            z = -1;
            scale = -1;
        }

        // This constructor is used for images.
        //template <class T>
        Asset(T _item, std::string _filename, int _x, int _y, int _z, float _scale)
        {
            item = _item;
            filename = _filename;
            x = _x;
            y = _y;
            z = _z;
            scale = _scale;
        }

        //Accessor method
        //template <class T>
        T getItem()
        {
            return item;
        }

    private:
		std::string filename;
		T item;
		int x, y, z;    // Where to place the asset
		float scale;
};
#endif
