import Foundation

struct Pair<T1: Hashable, T2: Hashable>: Hashable {
    let i: T1
    let j: T2
}

func P(_ p: (Int, Int)) -> Pair<Int,Int> {
    return Pair(i: p.0, j: p.1)
}

func P(_ i: Int, _ j: Int) -> Pair<Int,Int> {
    return Pair(i: i, j: j)
}

func readLines() -> [String] {
    var lines: [String] = []
    while let line = readLine(strippingNewline: true) {
        lines.append(line)
    }
    return lines
}

//if all(k1 == 0 and k2 == 0 or (i+k1, j+k2) not in T for k1 in (-1, 0, 1) for k2 in (-1, 0, 1)):
//  return (i, j)

func can_go(_ i: Int, _ j: Int) -> Bool {
    for k1 in (-1...1) {
        for k2 in (-1...1) {
            if (k1 == 0 && k2 == 0) {
                continue
            }
            if (T.contains(P(i + k1, j + k2))) {
                return false
            }
        }
    }
    return true;
}

func decide(_ round: Int, _ i: Int, _ j: Int) -> Pair<Int, Int> {
    if can_go(i, j) {
        return P(i, j)
    }

    let opts: [(Bool, (Int, Int))] = [
        ((-1...1).allSatisfy({ !T.contains(P(i - 1, j + $0)) }), (i - 1, j)),
        ((-1...1).allSatisfy({ !T.contains(P(i + 1, j + $0)) }), (i + 1, j)),
        ((-1...1).allSatisfy({ !T.contains(P(i + $0, j - 1)) }), (i, j - 1)),
        ((-1...1).allSatisfy({ !T.contains(P(i + $0, j + 1)) }), (i, j + 1))
    ]

    for k in 0...3 {
        let option = opts[(k + round) % 4]
        if option.0 {
            return P(option.1)
        }
    }

    return P(i, j)
}


let lines = readLines()
var T = Set<Pair<Int, Int>>()
for (i, line) in lines.enumerated() {
    for (j, cell) in line.enumerated() {
        if cell == "#" {
            T.insert(P(i, j))
        }
    }
}

var total1 = 0
var total2 = 0

for r in 0..<1000 {

    var Q = [Pair<Int, Int>: [Pair<Int, Int>]]()

    for p in T {
        Q[decide(r, p.i, p.j), default: []].append(p)
    }

    var N = Set<Pair<Int, Int>>()
    for (k, v) in Q {
        if v.count == 1 {
            N.insert(k)
        } else {
            N.formUnion(v)
        }
    }

    if r == 9 {
        let x = N.map({ $0.i }).max()! - N.map({ $0.i }).min()! + 1
        let y = N.map({ $0.j }).max()! - N.map({ $0.j }).min()! + 1
        total1 = x * y - T.count
    }

    if N == T {
        total2 = r + 1
        break
    }

    T = N
}

print(total1, total2)
