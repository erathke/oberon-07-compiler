
class Bubble {
	
	construct new(x, y) {
		 _x = x
		 _y = y
	}
	
	setX(x) { _x = x }
	x { _x }
	
	setY(y) { _y = y }
	y { _y }
}


class App {
	construct new() {}
	
	init() {
		System.print("init")
		var b1 = Bubble.new(100, 300)
		return b1
	}
	
	update(elapsedTime) {
		System.print("update %(elapsedTime)")
	}
	
	view(model) { 
		System.print("view")
	}
}

var app = App.new()

var update = Fn.new {|elapsedTime|
	app.update(elapsedTime)
}

