// https://thepythoncode.com/assistant/code-converter/python/swift/

import Foundation


func readLines() -> [String] {
    var lines: [String] = []
    while let line = readLine(strippingNewline: true) {
        lines.append(line)
    }
    return lines
}

func firstNumber(_ line: String) -> Int {
    let ret = line.first(where: {$0.isNumber})
    return Int(String(ret ?? "0")) ?? 0;
}

func lastNumber(_ line: String) -> Int {
    let ret = line.last(where: {$0.isNumber})
    return Int(String(ret ?? "0")) ?? 0;
}

func part1(_ values: [String]) -> Int {
    var ans1 = 0
    for line in values {
        ans1 += 10 * firstNumber(line) + lastNumber(line)
    }
    return ans1
}

let NUM = [
    "one"  ,
    "two"  ,
    "three",
    "four" ,
    "five" ,
    "six"  ,
    "seven",
    "eight",
    "nine" ,
]

/*
let pos = line.index(line.startIndex, offsetBy: idx)
let pre = String(line[..<pos])
let post = String(line[pos...])
if (num == post.prefix(num.count)) {
    print(line, pre, post)
    let resto = post.suffix(post.count-num.count)
    let newLine = pre + d + resto
    print(line, pre, d, resto)
    return parseLine(newLine)
}
*/

func parseLine(_ line: String) -> String {
    var dst: String = ""
    for (idx, c) in line.enumerated() {
        if (c.isNumber) {
            dst += String(c)
            continue
        }
        for (d, num) in NUM.enumerated() {
            let pos = line.index(line.startIndex, offsetBy: idx)
            let atu = String(line[pos...])
            if (atu.starts(with: num)) {
                dst += String(d+1)
                break
            }
        }
    }
    return dst
}

func part2(_ values: [String]) -> Int {
    var ans1 = 0
    for line in values {
        let L = parseLine(line)
        ans1 += 10 * firstNumber(L) + lastNumber(L)
    }
    return ans1
}


let values = readLines()

let ans1 = part1(values)
print(ans1)

let ans2 = part2(values)
print(ans2)
