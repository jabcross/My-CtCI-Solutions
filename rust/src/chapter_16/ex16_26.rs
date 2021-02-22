// 16.26 Calculator

use regex::Regex;

enum Ops {
    Plus,
    Minus,
}

fn calculator(expr: &str) -> f64 {
    let number_re = Regex::new(r"^[0-9]+").unwrap();
    let plus_re = Regex::new(r"^[+]").unwrap();
    let minus_re = Regex::new(r"^-").unwrap();
    let times_re = Regex::new(r"^[*]").unwrap();
    let div_re = Regex::new(r"^[/]").unwrap();
    let mut tail: &str = &expr;

    let mut numbers = Vec::new();
    let mut ops = Vec::new();

    loop {
        let mat = number_re.find(tail);
        if let Some(mat) = mat {
            numbers.push(mat.as_str().parse::<f64>().unwrap());
            tail = &tail[mat.end()..];
            continue;
        }
        let mat = plus_re.find(tail);
        if let Some(mat) = mat {
            ops.push(Ops::Plus);
            tail = &tail[mat.end()..];
            continue;
        }
        let mat = minus_re.find(tail);
        if let Some(mat) = mat {
            ops.push(Ops::Minus);
            tail = &tail[mat.end()..];
            continue;
        }
        let mat = times_re.find(tail);
        if let Some(mat) = mat {
            let a = numbers.pop().unwrap();
            tail = &tail[mat.end()..];
            let mat = number_re.find(tail).unwrap();
            tail = &tail[mat.end()..];
            let b = mat.as_str().parse::<f64>().unwrap();
            numbers.push(a * b);
            continue;
        }

        let mat = div_re.find(tail);
        if let Some(mat) = mat {
            let a = numbers.pop().unwrap();
            tail = &tail[mat.end()..];
            let mat = number_re.find(tail).unwrap();
            tail = &tail[mat.end()..];
            let b = mat.as_str().parse::<f64>().unwrap();
            numbers.push(a / b);
            continue;
        }
        break;
    }

    let mut numbers = numbers.iter();

    let mut acc = *numbers.next().unwrap();

    for op in ops {
        match op {
            Ops::Plus => {
                acc += numbers.next().unwrap();
            }
            Ops::Minus => {
                acc -= numbers.next().unwrap();
            }
        }
    }

    acc
}

pub fn test() {
    assert!(calculator("2*3+5/6*3+15") == 23.5);
    println!("Ex 16.26 ok!");
}
