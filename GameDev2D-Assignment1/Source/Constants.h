#pragma once

#include <GameDev2D.h>

// Player spawn position as a percentage of the screen width and height.
static const float PLAYER_SPAWN_POSITION_X_PCT = 0.5f;
static const float PLAYER_SPAWN_POSITION_Y_PCT = 0.5f;

// Player movement constants.
static const float PLAYER_TURN_SPEED = 360.0f; 
static const float PLAYER_ACCELERATION_RATE = 200.0f; 
static const float PLAYER_MAX_SPEED = 200.0f; 
static const int PLAYER_HEALTH = 1;
static const int PLAYER_COOLDOWN = 1;
static const int PLAYER_HEALT_MAX = 2;

// Player color.
static const GameDev2D::Color PLAYER_COLOR = GameDev2D::ColorList::White;

// Number of asteroids in the game.
const int NUM_ASTEROIDS = 20;

// Asteroid movement and appearance constants.
const float ASTEROID_MIN_SPEED = 20.0f; 
const float ASTEROID_MAX_SPEED = 70.0f; 
const float ASTEROID_MIN_ANGULAR_VELOCITY = 30.0f;  
const float ASTEROID_MAX_ANGULAR_VELOCITY = 180.0f; 
const int ASTEROID_MIN_SIDES = 10; 
const int ASTEROID_MAX_SIDES = 20; 
const float ASTEROID_MIN_RADIUS = 10.0f; 
const float ASTEROID_MAX_RADIUS = 30.0f;
const GameDev2D::Color ASTEROID_COLOR = GameDev2D::Color::Random(); 

// Bullet pool size.
const int BULLET_POOL_SIZE = 25;

// Bullet properties.
const int BULLET_RADIUS_INC = 3; 
const int BULLET_BURST_RADIUS_INC = 0; 
const int BULLET_CHARGED_RADIUS_INC = 0; 
const int BURST_FIRE_MAX = 20; 

const int CHARGED_FIRE_MAX = 25;
const int CHARGED_FIRE_DELAY = 100; 
const int CHARGED_MAX_SPEED = 600;


const int BULLET_OUTLINE = 1;
const float BULLET_TIME_ACTIVE = 2.0f; 
const float LASER_SPEED = 500.0f; 

// Bullet color.
static const GameDev2D::Color BULLET_COLOR = GameDev2D::Color::Random(); 
static const GameDev2D::Color BULLET_BURST_COLOR = GameDev2D::ColorList::Yellow; 
static const GameDev2D::Color BULLET_CHARGED_COLOR = GameDev2D::ColorList::Green; 

// Rapid fire interval.
const float RAPID_FIRE_INTERVAL = 0.0001f;

// Shield properties.
const int SHIELD_POOL_SIZE = 2; 
const float SHIELD_TIME_ACTIVE = 20.0f; 
const int SHIELD_SIZE = 2;

// Sound Properties
const float SOUND_VOLUME = 0.1f;

// Text Properties
const float TEXT_POS_X = 300.0f;
const float TEXT_POS_Y = 100.0f;

const float TEXT_POS_X_START = 240.0f;
const float TEXT_SIZE_START = 0.6f;


const float TEXT_POS_Y_NAME = 10.0f;
const float TEXT_SIZE_NAME = 0.3f;

// Random Properties
const int RAND_MIN = 1;
const int RAND_SHIELD = 7;
const int RAND_SOUND = 3;
