
class Bubble {
	static setX(x) { __x = x }
	static x { __x }
	
	static setY(y) { __y = y }
	static y { __y }
}

Bubble.setX(100)
Bubble.setY(300)

class GameEngine {
	
	foreign static bubble(x, y, radius, r, g, b, a)
	
	static update(elapsedTime) {
		var bx = Bubble.x
		var by = Bubble.y
		bubble(bx, by, 25.00, 255, 0, 0, 255)
		bubble(bx, by + 75, 25.00, 56, 109, 77, 255)
		bx = bx + 2
		if (bx >= 800 + (25.00 / 2)) {
			bx = - (25.00 / 2)
		}
		Bubble.setX(bx)
	}
}
