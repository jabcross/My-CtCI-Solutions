// 16.19 Pond Sizes

fn pond_sizes(height_map: &str)->Vec<usize>{
    // Returns areas of enclosed regions of value 0.
    // Uses a simple recursive flood algorithm.

    let mut rv = Vec::new();

    let mut height_map : Vec<Vec<i32>> = 
        height_map.split_terminator("\n")
        .map(|slice: &str|->Vec<i32> {
            slice.trim()
            .split_ascii_whitespace()
            .map(|text: &str| -> i32 {
                text.parse::<i32>().unwrap()})
            .collect()})
        .collect();

    // println!("{:?}", height_map);

    let mut current_id = -1;

    fn get_position(height_map: &mut Vec<Vec<i32>>, coords:(i32, i32))
            -> Option<&mut i32> {
        if coords.0 < 0 || coords.1 < 0 {None}
        else {
            match height_map.get_mut(coords.0 as usize) {
                Some(row) => row.get_mut(coords.1 as usize),
                None => None
            }
        }
    }

    fn get_neighborhood (coords:(i32, i32)) -> Vec<(i32, i32)> {
        let mut rv = Vec::new();
        for offset in &[(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)] {
            rv.push((coords.0 + offset.0, coords.1 + offset.1));
        }
        rv
    }

    fn flood(height_map: &mut Vec<Vec<i32>>, coords:(i32, i32), id: i32)
            -> usize {
        match get_position(height_map, coords) {
            Some(position) => {
                match *position {
                    0 => {
                        *position = id;
                        let mut acc = 1;
                        for neighbor_coord in get_neighborhood(coords) {
                            acc += flood(height_map, neighbor_coord, id);
                        }
                        return acc;
                    },
                    _ => 0
                }
            },
            None => 0
        }
    };

    for row in 0..height_map.len() {
        for column in 0..height_map[row].len() {
            let result = flood(&mut height_map, (row as i32, column as i32), current_id);
            if result != 0 {
                rv.push(result);
                current_id -= 1;
            }
        }
    }

    // println!("{:?}", height_map);

    rv
}

pub fn test() {

    let mut test = pond_sizes(
        "0 2 1 0
        0 1 0 1
        1 1 0 1
        0 1 0 1"
        );
    test.sort();
    // println!("{:?}", test);
    assert!(test.into_iter().zip(&[1,2,4]).all(|(a,b)| a == *b));
    println!("Ex 16.19 ok!");
}