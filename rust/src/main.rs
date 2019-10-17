mod chapter_1;
mod chapter_16;

fn main() {
    {   
        use crate::chapter_1::*;
        ex1_1::test();
        ex1_2::test();
        ex1_3::test();
    }

    {   
        use crate::chapter_16::*;
        ex16_16::test();
        ex16_17::test();
        ex16_18::test();
        ex16_19::test();
        ex16_20::test();
        ex16_21::test();
        ex16_22::test();
    }

    println!("Done");
}
