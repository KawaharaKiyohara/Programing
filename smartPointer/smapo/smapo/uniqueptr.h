#pragma once


//�Ȉ�UniquePtr
//std::unique_ptr���g�p���邱�Ƃ��������߂���B
template<class T>
class UniquePtr{
private:

    T * px;
    //�R�s�[�����Ƒ��d�ō폜�����̂ŃR�s�[�֎~�B
    //�|�C���^�̃R�s�[���������āA���L����K�v������ꍇ��
    //shared_ptr���g�p����
    UniquePtr(UniquePtr const &);
    UniquePtr & operator=(UniquePtr const &);

    void operator==( UniquePtr const& ) const;
    void operator!=( UniquePtr const& ) const;

public:

 	UniquePtr( T * p = 0 ): px( p )
    {
    }

	//�f�X�g���N�^�B
    ~UniquePtr() // never throws
    {
		delete px;
    }
	//���Z�b�g�B
    void reset(T * p = 0)
    {
		px = p;
    }

	//*���Z�q���I�[�o�[���[�h�B
    T & operator*() const 
    {
        return *px;
    }
    //�A���[���Z�q���I�[�o�[���[�h�B
    T * operator->() const
    {
        return px;
    }

	//���|�C���^���擾�B
    T * get() const 
    {
        return px;
    }

};