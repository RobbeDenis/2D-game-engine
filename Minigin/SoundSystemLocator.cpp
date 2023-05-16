#include "SoundSystemLocator.h"

std::unique_ptr<dae::SoundSystem> dae::SoundSystemLocator::_ss_instance{ std::make_unique<dae::null_SoundSystem>() };