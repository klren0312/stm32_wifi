app.filter("indoorFilter", function() {
    return function(indoor) {
        if (indoor === 1) {
            return "在屋内"
        } else {
            return "不在屋内"
        }
    }
})

app.filter("fengFilter", function() {
    return function(feng) {
        if (feng === 0) {
            return "风扇打开"
        } else {
            return "风扇关闭"
        }
    }
})

app.filter("timeFilter", function() {
    return function(time) {
        return new Date(time).toLocaleString()
    }
})
