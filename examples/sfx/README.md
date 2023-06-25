# SFX

- shows how to use `AssetsManager` to load and play sound effects and music.

<br>

## Sound effects

To use sound effects in SGE you should:

- Load sfx using `AssetsManager`:

```C++
    assetsManager->loadSFX(std::filesystem::current_path().string() + "/examples/sfx/assets/sfx.wav", "swordSwing");
```

- Fetch and play it where appropriate:

```C++
assetsManager->getSound("swordSwing")->play();
```

<br>

## Music

Because of the way [sf::Music](https://www.sfml-dev.org/documentation/2.6.0/classsf_1_1Music.php) is written, the approach is a bit different.

In short `sf::Music` streams music directly from the sound file unlike `sf::Sound` which plays sounds from memory.

<br>

So to play music in SGE you can:

- Save music location string in `AssetsManager` for easy access:

```C++
    assetsManager->specifyMusicLocation(std::filesystem::current_path().string() + "/examples/sfx/assets/music.wav", "battleMusic");
```

- Initialize `sf::Music` object:

```C++
sf::Music* music = new sf::Music();
```

- Specify music from saved location:

```C++
music->openFromFile(assetsManager->getMusicLocation("battleMusic"));
```

- Use `sf::Music` object as stated in SFML docs:

```C++
music->play();
```