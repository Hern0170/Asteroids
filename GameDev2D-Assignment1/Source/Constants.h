#pragma once

#include <GameDev2D.h>

static const float PLAYER_SPAWN_POSITION_X_PCT = 0.5f;
static const float PLAYER_SPAWN_POSITION_Y_PCT = 0.5f;

static const float PLAYER_TURN_SPEED = 360.0f; // Degrees per second.
static const float PLAYER_ACCELERATION_RATE = 200.0f; // Pixels per second per second.
static const float PLAYER_MAX_SPEED = 200.0f; // Pixels per second. 
static const int PLAYER_HEALTH = 1; // HEALTH

static const GameDev2D::Color PLAYER_COLOR = GameDev2D::ColorList::White;

const int NUM_ASTEROIDS = 80;

const float ASTEROID_MIN_SPEED = 20.0f; // Pixels per second. 
const float ASTEROID_MAX_SPEED = 70.0f; // Pixels per second. 
const float ASTEROID_MIN_ANGULAR_VELOCITY = 30.0f;  // Degrees per second.
const float ASTEROID_MAX_ANGULAR_VELOCITY = 180.0f; // Degrees per second.
const int ASTEROID_MIN_SIDES = 10;
const int ASTEROID_MAX_SIDES = 20;
const float ASTEROID_MIN_RADIUS = 10.0f;
const float ASTEROID_MAX_RADIUS = 30.0f;
//const GameDev2D::Color ASTEROID_COLOR = GameDev2D::ColorList::SlateGray;
const GameDev2D::Color ASTEROID_COLOR = GameDev2D::Color::Random();

const int BULLET_POOL_SIZE = 110;

const int BULLET_RADIUS_INC = 3;
const int BULLET_BURST_RADIUS_INC = 0;
const int BULLET_CHARGED_RADIUS_INC = 0;
const int BURST_FIRE_MAX = 20;

const int BULLET_OUTLINE = 1;
const float BULLET_TIME_ACTIVE = 2.0f;
const float LASER_SPEED = 500.0f;

static const GameDev2D::Color BULLET_COLOR = GameDev2D::Color::Random();
static const GameDev2D::Color BULLET_BURST_COLOR = GameDev2D::ColorList::Yellow;
static const GameDev2D::Color BULLET_CHARGED_COLOR = GameDev2D::ColorList::Green;


const float RAPID_FIRE_INTERVAL = 0.0001f;

const int SHIELD_POOL_SIZE = 2;
const float SHIELD_TIME_ACTIVE = 20.0f;


