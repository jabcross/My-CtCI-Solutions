// 16.22 Langton's Ant

// The grid will be represented by a map of coordinates.

#[derive(Copy, Clone, Debug, Hash, PartialEq, Eq)]
struct V2 {x:i32,y:i32}

use std::collections::HashMap;

impl std::ops::Add for V2 {
    type Output = Self;
    fn add(self, rhs: Self)->Self {
        V2{x:self.x + rhs.x, y:self.y + rhs.y}
    }
}

impl V2{

    pub fn rotate_cw (self) -> Self {
        V2{x:self.y, y:-self.x}
    }
    pub fn rotate_ccw (self) -> Self {
        V2{x:-self.y, y:self.x}
    }
}

const ZERO : V2 = V2{x:0, y:0};
const UP : V2 =  V2{x:0, y:1};
const DOWN : V2 =  V2{x:0, y:-1};
const LEFT : V2 =  V2{x:-1, y:0};
const RIGHT : V2 = V2{x:1, y:0};

struct State {
    
    board: HashMap<V2, bool>,
    current_position: V2,
    current_direction: V2, // normalized V2 in a cardinal direction
    min_pos: V2,
    max_pos: V2,

}

impl State {

    pub fn new() -> Self {
        let board = [(ZERO,false)].iter().cloned().collect::<HashMap<V2,bool>>();
        State {
            board,
            current_position: ZERO,
            current_direction: RIGHT,
            max_pos: ZERO,
            min_pos: ZERO,
        }
    }

    pub fn iterate(&mut self)  {
        let cell = self.board.entry(self.current_position).or_insert(false);
        if *cell == false { //white
            *cell = !*cell;
            self.current_direction = self.current_direction.rotate_cw();
        }
        else { // black
            *cell = !*cell;
            self.current_direction = self.current_direction.rotate_ccw();
        }
        self.current_position = self.current_position + self.current_direction;
        use std::cmp::{max,min};
        self.max_pos.x = max(self.max_pos.x, self.current_position.x);
        self.max_pos.y = max(self.max_pos.y, self.current_position.y);
        self.min_pos.x = min(self.min_pos.x, self.current_position.x);
        self.min_pos.y = min(self.min_pos.y, self.current_position.y);
    }

    pub fn to_string(&self)->String {
        let mut rv = String::new();
        // Print from top to bottom
        for y in (self.min_pos.y..=self.max_pos.y).rev() { 
            for x in self.min_pos.x..=self.max_pos.x {
                let pos = V2{x,y};
                rv += if pos == self.current_position {
                    match self.current_direction {
                        UP => "^",
                        DOWN => "v",
                        LEFT => "<",
                        RIGHT => ">",
                        _ => panic!("Invalid direction!")
                    }
                }
                else {
                    match self.board.get(&pos) {
                        Some(true) => "#",
                        _ => " ",
                    }
                }
            }
            rv += "\n";
        }
        rv
    }
}

fn print_k_moves(k: u32)->String {
    let mut state = State::new();

    for _ in 0..k {state.iterate()}
    state.to_string()
}

pub fn test(){
    assert!(print_k_moves(8) == &"
 ##
#<#
## 
"[1..]);
    println!("Ex 16.22 ok!");
}