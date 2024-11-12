class Texture {
	foreign static load(path)
}

class Ball {
	
	construct new(x, y, direction) {
		 _x = x
		 _y = y
		 _direction = direction
	}
	
	x() { _x }
	
	y() { _y }
	
	direction() { _direction }
	
	move(px) {
		_x = _x + (px * _direction)
		if (_x <= 0) {
			_direction = 1
		} 
		if (_x >= 736 ) {
			_direction = -1
		}
	}
}

class App {
	construct new() {
		_elapsedTime = 0.0
		_currentSprite = 0
	}
	
	foreign draw(texture, sprite, px, py)
	
	init() {
		_texture = Texture.load("assets/ball_frames.png")
		_b1 = Ball.new(100, 100, 1)
	}
	
	update(frameTick) {
		_elapsedTime = _elapsedTime + frameTick
		if (_elapsedTime > 0.0300) {
			_elapsedTime = 0.0
			_currentSprite = _currentSprite + _b1.direction()
			_currentSprite = _currentSprite % 4
		}
		_b1.move(4)
	}
	
	view() {
		var px = _b1.x()
		var py = _b1.y()
		draw(_texture, _currentSprite, px, py)
	}
}

var app = App.new()

var init = Fn.new {
	app.init()
}

var update = Fn.new {|frameTick|
	app.update(frameTick)
}

var view = Fn.new {
	app.view()
}
