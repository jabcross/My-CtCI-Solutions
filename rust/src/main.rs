mod chapter_1;

fn main() {
    {   
        use crate::chapter_1::*;
        ex1_1::test();
        ex1_2::test();
        ex1_3::test();
    }
    println!("Done");
}
