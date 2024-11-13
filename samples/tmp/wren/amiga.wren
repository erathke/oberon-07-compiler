
class Texture {
	foreign static load(path)
}

class Rectangle {
	construct new(x1, y1, x2, y2) {
		_x1 = x1
		_y1 = y1
		_x2 = x2
		_y2 = y2
	}
	
	x1() { _x1 }
	
	y1() { _y1 }
	
	x2() { _x2 }
	
	y2() { _y2 }
}

class Ball {
	
	construct new(x, y, direction, bounds) {
		 _x = x
		 _y = y
		 _direction = direction
		 _angleY = 47.cos
		 _bounds = bounds
	}
	
	static Width() { 64 }
	
	static Height() { 64 }
	
	x() { _x }
	
	y() { _y }
	
	direction() { _direction }
	
	foreign boing()
	
	move(px) {
		_x = _x + (px * _direction)
		_y = _y + (px * _direction * _angleY)
		if (_x <= _bounds.x1()) {
			_direction = 1
			_angleY = _angleY * -1
			boing()
		} 
		if (_x >= _bounds.x2() ) {
			_direction = -1
			_angleY = _angleY * -1
			boing()
		}
		
		if (_y <= _bounds.y1()) {
			_angleY = _angleY * -1
			boing()
		}
		
		if (_y >= _bounds.y2()) {
			_angleY = _angleY * -1
			boing()
		}
	}
}

class App {
	construct new(width, height, title) {
		_elapsedTime = 0.0
		_currentSprite = 0
		_texture = null
		_b1 = null
		_wwidth = width
		_wheight = height
		_wtitle = title
	}
	
	foreign draw(texture, sprite, bx, by, bw, bh)
	
	foreign initWindow(width, height, title)
	
	init() {
		// must be called before loading textures
		initWindow(_wwidth, _wheight, _wtitle)
		_texture = Texture.load("assets/ball_frames.png")
		var bounds = Rectangle.new(0, 0, _wwidth - Ball.Width() , _wheight - Ball.Height()) 
		_b1 = Ball.new(100, 100, 1, bounds)
	}
	
	update(frameTick) {
		_elapsedTime = _elapsedTime + frameTick
		if (_elapsedTime > 0.0400) {
			_elapsedTime = 0.0
			_currentSprite = _currentSprite + _b1.direction()
			_currentSprite = _currentSprite % 4
		}
		_b1.move(3)
	}
	
	view() {
		var bx = _b1.x()
		var by = _b1.y()
		var bw = Ball.Width()
		var bh = Ball.Height()
		draw(_texture, _currentSprite, bx, by, bw, bh)
	}
}

var app = App.new(480, 320, "Amiga - boing ball")

var init = Fn.new {
	app.init()
}

var update = Fn.new {|frameTick|
	app.update(frameTick)
}

var view = Fn.new {
	app.view()
}
