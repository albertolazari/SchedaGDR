#ifndef DIE_H
#define DIE_H

class Die {
private:
    unsigned faces;
public:
    Die(unsigned = 0);
    unsigned roll()const;

    unsigned getFaces() const;

    bool operator==(const Die&) const;
    bool operator!=(const Die&) const;
    bool operator<(const Die&) const;
    bool operator>(const Die&) const;
};

#endif // DIE_H
