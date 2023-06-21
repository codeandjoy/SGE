# Simple Game Engine

A game engine written on top of [SFML](https://www.sfml-dev.org/) library.

<br>

## Usage

Grab the `SGE.hpp` source file.

Include it in your project.

Follow the global code structure and have fun:

```C++
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SGE.hpp"

int main(){
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");

    sge::Universe* universe = new sge::Universe(window);
    // Optional debug functionality initialization

    // Your game code

    universe->loop(); // Starting the universe loop

    return 0;
}
```

<br>

## Documentation

You can find in depth documentation in `/src/*` subdirectories and usage explanations in `/examples/*` subdirectories.

Start with learning [structure and key concepts](./src/Structure/README.md) of the engine.

<br>

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Feel free to suggest ideas and improvements on [twitter](https://twitter.com/codeandjoy).

<br>

## License

[MIT](https://choosealicense.com/licenses/mit/)