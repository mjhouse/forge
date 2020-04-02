#ifndef __FMODELLINE_H__
#define __FMODELLINE_H__

class ILine {
public:

	virtual ~ILine() = default;

	virtual void setStart(const QVector3D& t_start) {};

	virtual void setEnd(const QVector3D& t_end) {};

};

class HasLine : public ILine {
public:
	void setStart(const QVector3D& t_start) override {};

	void setEnd(const QVector3D& t_end) override {};
};

class NoLine : public ILine {};

class FObject {
private:
	ILine* m_line;

public:

	FObject(ILine* t_line)
		: m_line(t_line) {}

	void setStart(const QVector3D& t_start) { m_line->setStart(t_start); };

	void setEnd(const QVector3D& t_end) { m_line->setEnd(t_end); };

	bool isLine() { return  }

};

#endif